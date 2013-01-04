#include <curl/curl.h>

int main()
{
    CURL * curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "Failure\n");

        curl_easy_cleanup(curl);
    }
    else
        printf("Something ain't right.\n");

    return 0;
}
