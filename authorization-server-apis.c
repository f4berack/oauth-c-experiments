#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8080

static int answer_to_request(void *cls, struct MHD_Connection *connection,
                             const char *url, const char *method,
                             const char *version, const char *upload_data,
                             size_t *upload_data_size, void **con_cls) {

    
    if (strcmp(method, "POST") == 0 && strcmp(url, "/hello")) {
        const char *response_text = "Hello, World!";
        struct MHD_Response *response;
        int ret;

        response = MHD_create_response_from_buffer(strlen(response_text),
                                                   (void*)response_text, MHD_RESPMEM_PERSISTENT);

        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL,
                              &answer_to_request, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        fprintf(stderr, "Failed to start HTTP server\n");
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

