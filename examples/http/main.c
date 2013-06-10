#include <stdio.h>
#include <string.h>

typedef enum {
    HTTP_HEAD,
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE
} http_method;

typedef enum {
    HTTP_STATUS_NONE = 0,
    HTTP_STATUS_OK = 200,
    HTTP_STATUS_FORBIDDEN = 403,
    HTTP_STATUS_NOTFOUND = 404
} http_status;

typedef struct {
    http_method method;
    char url[256];
} http_request;

typedef struct {
    http_status status;
    char header[256];
} http_response;

int http_send(const http_request* req, http_response* res);

int main(void)
{
    http_request req[4] = {
        {
            HTTP_GET,
            "http://example.net"
        },
        {
            HTTP_GET,
            "http://403.example.net"
        },
        {
            HTTP_GET,
            "http://404.example.net"
        },
        {
            HTTP_GET,
            "http://none.example.net"
        }
    };

    int num_req = sizeof(req) / sizeof(http_request);
    int i = 0;
    for (i = 0; i < num_req; i++) {
        http_response res = { HTTP_STATUS_NONE, "" };
        printf("%s ....\n", req[i].url);
        if (http_send(&req[i], &res)) {
            printf("status = %d\n", res.status);
            if (res.header[0] != '\0') {
                printf("%s\n", res.header);
            }
        } else {
            printf("status = %d\n", res.status);
        }
        puts("");
    }
}

int http_send(const http_request* req, http_response* res)
{
    int retval = 1;

    if (strcmp(req->url, "http://example.net") == 0) {
        res->status = HTTP_STATUS_OK;
        strcpy(res->header, "Content-Type: text/html");
    }
    else if (strcmp(req->url, "http://403.example.net") == 0) {
        res->status = HTTP_STATUS_FORBIDDEN;
        strcpy(res->header, "");
    }
    else if (strcmp(req->url, "http://404.example.net") == 0) {
        res->status = HTTP_STATUS_NOTFOUND;
        strcpy(res->header, "");
    }
    else {
        res->status = HTTP_STATUS_NONE;
        strcpy(res->header, "");
        retval = 0;
    }

    return retval;
}
