/*
 * kc_jwt.h - JWKS fetching and JWT validation for libkc
 *
 * Validates JWT tokens locally using cached JWKS (JSON Web Key Sets)
 * fetched from Keycloak. Supports RS256 signatures.
 *
 * Ported from X3's kc_jwt.c.
 */

#ifndef KC_JWT_H
#define KC_JWT_H

#include "kc_realm.h"     /* for struct kc_realm */

/* Forward declaration — defined in kc_keycloak.h (libkc) or keycloak.h (X3) */
struct kc_token_info;

/* JWT statistics */
struct kc_jwt_stats {
    unsigned long jwks_cache_hits;
    unsigned long jwks_cache_misses;
};

/* Initialize JWT subsystem */
void kc_jwt_init(void);

/* Shutdown and free JWKS cache */
void kc_jwt_cleanup(void);

/* Get JWT stats snapshot */
void kc_jwt_stats_get(struct kc_jwt_stats *out);

/* Validate a JWT token locally using cached JWKS keys.
 * Fetches/refreshes JWKS from Keycloak if needed (sync HTTP).
 * @param realm   Keycloak realm config (for JWKS endpoint)
 * @param token   Raw JWT string
 * @param info_out Output: parsed claims (caller must free with kc_jwt_token_info_free)
 * @return KC_SUCCESS (0), KC_FORBIDDEN (-3), or KC_ERROR (-1)
 */
int kc_jwt_validate_local(struct kc_realm realm, const char *token,
                          struct kc_token_info **info_out);

/* Free a kc_token_info allocated by kc_jwt_validate_local.
 * Frees both the fields and the struct itself. */
void kc_jwt_token_info_free(struct kc_token_info *info);

#endif /* KC_JWT_H */
