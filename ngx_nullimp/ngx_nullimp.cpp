////////
extern "C" {
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>
};

extern "C" {
#include "thpool.h"
};

#include <pthread.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "impfactory.h"
#include "baseimp.h"
#include "imparam.h"

#include <wand/magick_wand.h>
#define radius2index(r, cglcf) (r-(cglcf)->min_radius)/(cglcf)->step_radius
#include "gmimp.h"

/////// 前置定义函数
static char* ngx_http_nullimp(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static char *test_src_data = NULL;
static int test_src_len = 0;

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

static thpool_t * gthp = NULL;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *imp_thread_proc(void *arg)
{
    ngx_int_t rc;
    ngx_buf_t *b, pb;
    ngx_chain_t out;

    ngx_http_request_t *r = (ngx_http_request_t *)arg;
    std::cout<<"222r-main-connt:"<<r->main->count<<std::endl;

    GmImp *imp = new GmImp();
    imp->process("ab/cb/g/efkjdsoifds_p12_mk456.jpg");

    size_t img_length;
    u_char *img_data = imp->get_result(&img_length);

    char *ct = "image/jpeg";
    r->headers_out.content_type.len = strlen(ct);
    r->headers_out.content_type.data = (u_char*)(ct);


    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = img_length ; // 5;

    b = (ngx_buf_t*)ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    // b = &pb;
    out.buf = b;
    out.next = NULL;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    // 
    char *resp = "12345";
    // b->pos = (u_char*)resp;
    // b->last = (u_char*)(resp + 5);

    b->pos = (u_char*)img_data;
    b->last = (u_char*)(img_data + img_length);

    b->memory = 1;
    b->last_buf = 1;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler1");    
    rc = ngx_http_send_header(r);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler2");    

    rc = ngx_http_output_filter(r, &out);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler:%%d");    

    delete imp;

    // sleep(3);
    std::cout<<"imp thread done111"<<std::endl;
    pthread_mutex_lock(&g_mutex);
    ngx_http_finalize_request(r, NGX_DONE);
    pthread_mutex_unlock(&g_mutex);
    std::cout<<"imp thread done222 "<<std::endl;
}

// 图片结果输出
static int nimp_fill_output_image(BaseImp *himp, ngx_http_request_t *r, ngx_chain_t *out)
{
    ngx_buf_t *b;

    std::string mimeType, imgData;

    
    mimeType = himp->mimeType();
    imgData = himp->data();

    std::cout<<__LINE__ << "get result:" <<mimeType << imgData.length()  << std::endl;

    r->headers_out.content_type.len = mimeType.length();
    r->headers_out.content_type.data = (u_char*)mimeType.c_str();

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = imgData.length();


    b = (ngx_buf_t*)ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out->buf = b;
    out->next = NULL;

    b->pos = (u_char*)imgData.c_str();
    b->last = (u_char*)(imgData.c_str() + imgData.length());

    b->memory = 1;
    b->last_buf = 1;


    return 0;
}

static char *nimp_read_image_file(char *file, char *buff, int *len)
{
    // char *buff = 0;
    char rb[8192] = {0};
    int rc;

    // buff = (char*) calloc(1024 * 1024, 1);
    FILE *fp = fopen(file, "r");

    *len = 0;
    while (!feof(fp)) {
        rc = fread(rb, 8192, 1, fp);
        memcpy(buff + *len, rb, ftell(fp) - *len);
        *len = ftell(fp);
    }

    buff[*len] = 0;

    fclose(fp);

    return buff;
}



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

    ////////////
    size_t img_length;
    u_char *img_data;
    GmImp *imp;// = new GmImp();
    /*
    imp->process("ab/cb/g/efkjdsoifds_p12_mk456.jpg");

    img_data = imp->get_result(&img_length);

    std::cout<<"r-main-connt:"<<r->main->count<<std::endl;
    std::cout<<"got img length:"<<img_length<<std::endl;
    */
    // r->main->count += 1; // 这句代码这么管用啊！！！

    // pthread_t pth;
    // int pcr;
    // pcr = pthread_create(&pth, NULL, imp_thread_proc, (void*)r);
    // thpool_add_work(gthp, imp_thread_proc, (void*)r);

    Imparam *impa = new Imparam((const char*)r->uri.data, r->uri.len);
    impa->parseParam();
    impa->dumpParam();

    struct timeval btv, etv;
    // char fbuff[1024*1024] = {0};
    char *fbuff = 0;
    int flen;

    BaseImp *himp = ImpFactory::create(ImpFactory::IMP_TYPE_OPENCV);
    // BaseImp *himp = ImpFactory::create(ImpFactory::IMP_TYPE_GMAGICK);
    // std::string tname = himp->resizeFile("/home/gzleo/shots/nshots93.jpg", 200, 100);


    // nimp_read_image_file("/home/gzleo/shots/nshots93.jpg", fbuff, &flen);
    fbuff = test_src_data;
    flen = test_src_len;
    std::cout<<"read file content done"<<flen<<"\n";

    gettimeofday(&btv,0);

    switch (impa->m_operator) {
    case Imparam::OP_RESIZE: {
        std::cout<<"before call resizebuff"<<himp<<std::endl;
        std::string tname = himp->resizeBuffer((const unsigned char*)fbuff, flen, 200, 100);
        std::cout<<"file name:" << tname<<(&tname) << std::endl;
    }
    case Imparam::OP_PHASH:
    default:
        break;
    };

    gettimeofday(&etv, 0);
    std::cout<<"used time:" << (etv.tv_sec - btv.tv_sec) << " ms:" << (etv.tv_usec - btv.tv_usec)/1000.0 << std::endl;
    
    nimp_fill_output_image(himp, r, &out);
    
    ImpFactory::free(himp, ImpFactory::IMP_TYPE_OPENCV);
    delete impa; impa = 0;
    // sleep(50);

    rc = ngx_http_send_header(r);
    rc = ngx_http_output_filter(r, &out);

    return NGX_OK;
    // delete imp;
    ////////////

    
    // r->headers_out.content_type.len = sizeof("text/html")-1;
    // r->headers_out.content_type.data = (u_char*)("text/html");

    char *ct = "image/jpeg";
    r->headers_out.content_type.len = strlen(ct);
    r->headers_out.content_type.data = (u_char*)(ct);


    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = img_length ; // 5;

    b = (ngx_buf_t*)ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out.buf = b;
    out.next = NULL;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    // 
    char *resp = "12345";
    // b->pos = (u_char*)resp;
    // b->last = (u_char*)(resp + 5);

    b->pos = (u_char*)img_data;
    b->last = (u_char*)(img_data + img_length);

    b->memory = 1;
    b->last_buf = 1;

    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    
    rc = ngx_http_send_header(r);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    rc = ngx_http_output_filter(r, &out);
    ngx_log_debug0(NGX_LOG_INFO, r->connection->log, 0, "enter nullimp handler");    

    delete imp;

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

    if (gthp == NULL) {
        gthp = thpool_init(3);
    }

    test_src_data = (char*)calloc(1024 * 1024, 1);
    nimp_read_image_file("/home/gzleo/shots/nshots93.jpg", test_src_data, &test_src_len);

    ngx_log_debug0(NGX_LOG_INFO, cf->log, 0, "enter nullimp module222");

    if (!gthp) {
        return (char*)NGX_CONF_ERROR;
    }
    return NGX_CONF_OK;
    return NULL;
}


