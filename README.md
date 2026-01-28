# libkc - Keycloak Client Library

Shared C library for Keycloak HTTP operations, used by both [X3 Services](https://github.com/evilnet/x3) and [Nefarious IRCd](https://github.com/evilnet/nefarious2).

## Overview

libkc provides a portable Keycloak REST API client with:

- **Async HTTP** (`kc_http`) - Non-blocking HTTP via curl_multi, driven by an application-provided event loop
- **Sync HTTP** (`kc_http_sync`) - Blocking HTTP with retry logic and latency stats
- **Keycloak REST client** (`kc_keycloak`) - Token management, user CRUD, group operations, token introspection
- **JWT validation** (`kc_jwt`) - Local RS256 JWT validation with JWKS caching
- **URL builders** (`kc_url`) - All Keycloak REST API endpoint URLs
- **Webhook delivery** (`kc_webhook`) - HTTP webhook notifications for user events
- **Caching** (`kc_cache`) - User ID and representation caches with configurable TTL
- **Base64** (`kc_base64`) - Base64/base64url encode/decode (used by JWT)

## Architecture

libkc is application-agnostic. It requires two adapter interfaces at init:

- **Event loop adapter** (`kc_event.h`) - Timer and file descriptor registration for async I/O
- **Log adapter** (`kc_log.h`) - Logging callback with severity levels

```c
#include <kc/kc.h>
#include <kc/kc_keycloak.h>

/* Provide event loop and logging adapters */
kc_init(&my_event_ops, &my_log_ops);

/* Configure and use Keycloak operations */
struct kc_config config = {
    .base_url = "http://keycloak:8080",
    .realm = "master",
    .client_id = "my-client",
    .client_secret = "secret"
};
kc_keycloak_init(&config);
```

## Modules

| Header | Source | Description |
|--------|--------|-------------|
| `kc.h` | `kc.c` | Init, shutdown, logging macros |
| `kc_event.h` | - | Event loop adapter interface |
| `kc_log.h` | - | Log adapter interface |
| `kc_realm.h` | - | `struct kc_realm` (base_url + realm name) |
| `kc_http.h` | `kc_http.c` | Async HTTP (curl_multi) |
| `kc_http_sync.h` | `kc_http_sync.c` | Sync HTTP (curl_easy) with retry |
| `kc_keycloak.h` | `kc_keycloak.c` | Keycloak REST API client (async) |
| `kc_url.h` | `kc_url.c` | Keycloak endpoint URL builders |
| `kc_jwt.h` | `kc_jwt.c` | JWKS fetch + JWT RS256 validation |
| `kc_base64.h` | `kc_base64.c` | Base64 encode/decode |
| `kc_cache.h` | `kc_cache.c` | User ID + representation caches |
| `kc_webhook.h` | `kc_webhook.c` | Webhook HTTP delivery |

## Building

### Dependencies

- libcurl (`libcurl4-openssl-dev`)
- jansson (`libjansson-dev`)
- OpenSSL (`libssl-dev`) - for JWT/JWKS support

### Build

```bash
autoreconf -fi
./configure --prefix=/usr
make
make install
```

### Linking

```
# pkg-config style (if installed)
gcc myapp.c -lkc -lcurl -ljansson -lssl -lcrypto

# Headers install to <prefix>/include/kc/
#include <kc/kc.h>
#include <kc/kc_keycloak.h>
```

## Integration

### X3 Services

X3 links against libkc and provides adapters in:
- `x3_kc_adapter.c` - Bridges X3's ioset event loop to `kc_event_ops`
- `x3_kc_bridge.c` - Bridges X3's HTTP submission to libkc's async HTTP

### Nefarious IRCd

Nefarious provides its own adapters:
- `ircd_kc_adapter.c` - Bridges Nefarious's event engine to `kc_event_ops`

## License

GPL-2.0-or-later (matching X3 and Nefarious)
