////////
extern "C" {
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>
};

#include <wand/magick_wand.h>
#define radius2index(r, cglcf) (r-(cglcf)->min_radius)/(cglcf)->step_radius

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/////// 前置定义函数
static char* ngx_http_nullimp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

typedef struct {

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
    ngx_int_t rc;
    ngx_buf_t *b;
    ngx_chain_t out;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    
    rc = ngx_http_discard_request_body(r);
    if (rc != NGX_OK && rc != NGX_AGAIN) {
        return rc;
    }
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    
    
    r->headers_out.content_type.len = sizeof("text/html")-1;
    r->headers_out.content_type.data = (u_char*)("text/html");

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = 5;

    b = (ngx_buf_t*)ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out.buf = b;
    out.next = NULL;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    // 
    char *resp = "12345";
    b->pos = (u_char*)resp;
    b->last = (u_char*)(resp + 5);

    b->memory = 1;
    b->last_buf = 1;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    
    rc = ngx_http_send_header(r);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    rc = ngx_http_output_filter(r, &out);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    // return rc;
    // return NGX_DONE;
    // return NGX_AGAIN;
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


