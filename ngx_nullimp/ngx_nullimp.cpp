////////
extern "C" {
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>
};

#include <wand/magick-wand.h>
#define radius2index(r, cglcf) (r-(cglcf)->min_radius)/(cglcf)->step_radius

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/////// 前置定义函数
static char* ngx_http_nullimp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

typedef struct {
    ngx_uint_t   max_radius;
    ngx_uint_t   min_radius;
    ngx_uint_t   step_radius;
    unsigned char** circle_templates;
    size_t* circle_sizes;
    ngx_flag_t           enable;
} ngx_http_nullimp_loc_conf_t;

static ngx_command_t  ngx_http_nullimp_commands[] = {
    { ngx_string("nullimp"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_http_nullimp,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};

// ngx_http_nullimp_module
static ngx_http_module_t  ngx_http_nullimp_module_ctx = {
    NULL, // ngx_http_circle_gif_preconf,   /* preconfiguration */
    NULL, // ngx_http_circle_gif_postconf,  /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    NULL, // ngx_http_circle_gif_create_loc_conf,  /* create location configuration */
    NULL  // ngx_http_circle_gif_merge_loc_conf /* merge location configuration */
};


ngx_module_t  ngx_http_nullimp_module = {
    NGX_MODULE_V1,
    &ngx_http_nullimp_module_ctx, /* module context */
    ngx_http_nullimp_commands,   /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};



//// 实现

static ngx_int_t ngx_http_nullimp_handler(ngx_http_request_t *r)
{
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    
    return NGX_OK;
}


static char* ngx_http_nullimp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_log_debug0(NGX_LOG_INFO, cf->log, 0, "enter nullimp module");
    ngx_http_core_loc_conf_t  *clcf;
    ngx_http_nullimp_loc_conf_t *cglcf = (ngx_http_nullimp_loc_conf_t*)conf;

    clcf = (ngx_http_core_loc_conf_t*)ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_nullimp_handler;

    // cglcf->enable = 1;

    return NGX_CONF_OK;
    return NULL;
}


