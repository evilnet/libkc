/*
 * kc_keycloak.c - Keycloak REST API client
 *
 * Stub implementation. Will be populated during Phase C by extracting
 * operations from X3's keycloak.c.
 */

#include "kc_keycloak.h"
#include "kc.h"
#include "kc_http.h"

#include <stdlib.h>
#include <string.h>

/* Internal state */
static struct kc_config g_config;
static struct kc_access_token *g_cached_token = NULL;
static int g_initialized = 0;

static struct kc_keycloak_stats g_kc_stats;

int kc_keycloak_init(const struct kc_config *config)
{
    if (g_initialized || !config)
        return -1;

    memset(&g_config, 0, sizeof(g_config));
    if (config->base_url)
        g_config.base_url = strdup(config->base_url);
    if (config->realm)
        g_config.realm = strdup(config->realm);
    if (config->client_id)
        g_config.client_id = strdup(config->client_id);
    if (config->client_secret)
        g_config.client_secret = strdup(config->client_secret);

    memset(&g_kc_stats, 0, sizeof(g_kc_stats));
    g_initialized = 1;

    kc_log_info("kc_keycloak: initialized for %s realm=%s",
                g_config.base_url ? g_config.base_url : "(null)",
                g_config.realm ? g_config.realm : "(null)");

    return 0;
}

void kc_keycloak_shutdown(void)
{
    if (!g_initialized)
        return;

    free((void *)g_config.base_url);
    free((void *)g_config.realm);
    free((void *)g_config.client_id);
    free((void *)g_config.client_secret);
    memset(&g_config, 0, sizeof(g_config));

    if (g_cached_token) {
        kc_access_token_free(g_cached_token);
        g_cached_token = NULL;
    }

    g_initialized = 0;
    kc_log_info("kc_keycloak: shutdown");
}

/* --- Stub implementations (Phase C will replace these) --- */

int kc_token_ensure(kc_token_cb cb, void *data)
{
    (void)cb; (void)data;
    /* TODO: Phase C - implement token acquisition/refresh */
    return -1;
}

const struct kc_access_token *kc_token_cached(void)
{
    return g_cached_token;
}

int kc_user_get(const char *username, kc_user_cb cb, void *data)
{
    (void)username; (void)cb; (void)data;
    return -1;
}

int kc_user_get_by_id(const char *id, kc_user_cb cb, void *data)
{
    (void)id; (void)cb; (void)data;
    return -1;
}

int kc_user_search(const char *query, bool exact, kc_users_cb cb, void *data)
{
    (void)query; (void)exact; (void)cb; (void)data;
    return -1;
}

int kc_user_create(const char *username, const char *email,
                   const char *cred_data, const char *secret_data,
                   kc_result_cb cb, void *data)
{
    (void)username; (void)email; (void)cred_data; (void)secret_data;
    (void)cb; (void)data;
    return -1;
}

int kc_user_delete(const char *id, kc_result_cb cb, void *data)
{
    (void)id; (void)cb; (void)data;
    return -1;
}

int kc_user_update(const char *id, json_t *repr, kc_result_cb cb, void *data)
{
    (void)id; (void)repr; (void)cb; (void)data;
    return -1;
}

int kc_user_set_password(const char *id, const char *password,
                         kc_result_cb cb, void *data)
{
    (void)id; (void)password; (void)cb; (void)data;
    return -1;
}

int kc_user_verify_password(const char *username, const char *password,
                            kc_token_cb cb, void *data)
{
    (void)username; (void)password; (void)cb; (void)data;
    return -1;
}

int kc_user_get_groups(const char *user_id, kc_groups_cb cb, void *data)
{
    (void)user_id; (void)cb; (void)data;
    return -1;
}

int kc_user_add_group(const char *user_id, const char *group_id,
                      kc_result_cb cb, void *data)
{
    (void)user_id; (void)group_id; (void)cb; (void)data;
    return -1;
}

int kc_user_remove_group(const char *user_id, const char *group_id,
                         kc_result_cb cb, void *data)
{
    (void)user_id; (void)group_id; (void)cb; (void)data;
    return -1;
}

int kc_token_introspect(const char *token, kc_introspect_cb cb, void *data)
{
    (void)token; (void)cb; (void)data;
    return -1;
}

int kc_jwks_refresh(kc_result_cb cb, void *data)
{
    (void)cb; (void)data;
    return -1;
}

int kc_token_verify_offline(const char *token, struct kc_token_info *info)
{
    (void)token; (void)info;
    return -1;
}

void kc_keycloak_stats_get(struct kc_keycloak_stats *out)
{
    if (out)
        *out = g_kc_stats;
}

/* --- Memory management --- */

void kc_access_token_free(struct kc_access_token *token)
{
    if (!token)
        return;
    free(token->access_token);
    free(token->refresh_token);
    free(token->token_type);
    free(token->session_state);
    free(token->scope);
    free(token);
}

void kc_user_free(struct kc_user *user)
{
    if (!user)
        return;
    free(user->id);
    free(user->username);
    free(user->email);
}

void kc_token_info_free(struct kc_token_info *info)
{
    if (!info)
        return;
    free(info->username);
    free(info->email);
    free(info->sub);
}

void kc_group_free(struct kc_group *group)
{
    if (!group)
        return;
    free(group->id);
    free(group->name);
    free(group->path);
}
