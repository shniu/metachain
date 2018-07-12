/*
#include <iostream>
#include "hello.h"
#include "mongoose.h"

static const char *s_http_port = "6666";
static const mg_str s_get_method = MG_MK_STR("GET");
static const mg_str s_post_method = MG_MK_STR("POST");

// is_equal
static int is_equal(const struct mg_str *s1, const struct mg_str *s2) {
    return s1->len == s2->len && memcmp(s1->p, s2->p, s1->len) == 0;
}

static void ev_handler(struct mg_connection *c, int ev, void *p) {
    */
/*if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        // We have received an HTTP request. Parsed request is contained in `hm`.
        // Send HTTP reply to the client which shows full original request.
        mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
        mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
    }*//*

    static const struct mg_str api_prefix = MG_MK_STR("/api/v1");
    struct http_message *hm = (struct http_message *) p;
    struct mg_str key;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            hello("http...");
            // get
            if (is_equal(&hm->method, &s_get_method)) {
                mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
                mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
            }
            break;
        default:
            hello("default...");
            break;
    }
}

int main() {
    std::cout << "C++: Hello, World!" << std::endl;
    hello("C++");

    struct mg_mgr mgr;
    struct mg_connection *c;

    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(c);

    for (;;) {
        mg_mgr_poll(&mgr, 500);
    }
    mg_mgr_free(&mgr);

    return 0;
}*/

#include "mongoose.h"

#include <string>

//定义web服务端口号
static const char *s_http_port = "8055";

//post和get请求分类
static const struct mg_str s_get_method = MG_MK_STR("GET");
static const struct mg_str s_post_method = MG_MK_STR("POST");

//几个辅助函数
//判断前缀

static int has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
    return uri->len > prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
}

//判断相同

static int is_equal(const struct mg_str *s1, const struct mg_str *s2) {
    return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;
}

//get请求下的简单求和

static void handle_sum_call_get(struct mg_connection *nc, struct http_message *hm) {

    std::string n1, n2;

    double result;

    /* Get form variables */
    mg_get_http_var(&hm->query_string, "n1", &n1[0], sizeof(n1));
    mg_get_http_var(&hm->query_string, "n2", &n2[0], sizeof(n2));

    /* Send headers */
    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */

    result = strtod(n1.c_str(), NULL) + strtod(n2.c_str(), NULL);

    mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);

    mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */

}

//post请求下的简单求和

static
void
handle_sum_call_post(struct
                             mg_connection *nc, struct
                             http_message *hm) {

    char
            n1[100], n2[100];

    double
            result;

    /* Get form variables */

    mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));

    mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));

    /* Send headers */

    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */

    result = strtod(n1, NULL) + strtod(n2, NULL);

    mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);

    mg_send_http_chunk(nc, "", 0); /* Send empty chunk, the end of response */

}

//网络请求处理回调函数

//struct mg_connection *c 和客户端建立的请求链接，给客户端返回数据时需要

//int ev 应该时请求类型

//void *ev_data 客户端发送来的整个请求数据

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {

    //if (ev == MG_EV_HTTP_REQUEST) {

    //    struct http_message *hm = (struct http_message *) ev_data;

    //    // We have received an HTTP request. Parsed request is contained in `hm`.

    //    // Send HTTP reply to the client which shows full original request.

    //    mg_send_head(nc, 200, hm->message.len, "Content-Type: text/plain");

    //    mg_printf(nc, "%.*s", (int)hm->message.len, hm->message.p);

    //}

    static const struct mg_str api_prefix = MG_MK_STR("/api/v1");

    struct http_message *hm = (struct http_message *) ev_data;

    struct mg_str key;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:

            //校验请求地址是否符合规定的约定的前缀

            if (has_prefix(&hm->uri, &api_prefix)) {

                key.p = hm->uri.p + api_prefix.len;

                key.len = hm->uri.len - api_prefix.len;

                //分方法处理

                if (is_equal(&hm->method, &s_get_method)) {

                    //get请求

                    if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {

                        handle_sum_call_get(nc, hm); /* Handle RESTful call */

                    }

                } else if (is_equal(&hm->method, &s_post_method)) {

                    //post请求

                    if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {

                        handle_sum_call_post(nc, hm); /* Handle RESTful call */

                    }

                } else {

                    //其他请求类型的不做处理
                    mg_printf(nc, "%s",

                              "HTTP/1.0 501 Not Implemented\r\n"

                                      "Content-Length: 0\r\n\r\n");

                }

            } else {

                //请求非法时，不处理

                mg_str
                        re = mg_mk_str("该请求无法处理");

                mg_send_head(nc, 200, re.len, "Content-Type: text/plain");

                mg_printf(nc, "%.*s", (int) re.len, re.p);

            }

            break;

        default:

            break;

    }

}

//主体服务

int main(void) {

    struct mg_mgr mgr;

    struct mg_connection *c;

    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(c);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}

