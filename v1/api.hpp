#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <curl/curl.h>

std::string Link = "https://vidsrc.me/";
std::string ApiKey = "";
std::map<std::string, std::string> Query;

std::string httpGet(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, std::string* s) -> size_t {
            size_t totalSize = size * nmemb;
            s->append(static_cast<char*>(contents), totalSize);
            return totalSize;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return response;
}

struct AFMA {
    struct Genre {
        Json::Value get_movie() {
            std::string json_str = R"({"genres":[{"id":28,"name":"Action"},{"id":12,"name":"Adventure"},{"id":16,"name":"Animation"},{"id":35,"name":"Comedy"},{"id":80,"name":"Crime"},{"id":99,"name":"Documentary"},{"id":18,"name":"Drama"},{"id":10751,"name":"Family"},{"id":14,"name":"Fantasy"},{"id":36,"name":"History"},{"id":27,"name":"Horror"},{"id":10402,"name":"Music"},{"id":9648,"name":"Mystery"},{"id":10749,"name":"Romance"},{"id":878,"name":"Science Fiction"},{"id":10770,"name":"TV Movie"},{"id":53,"name":"Thriller"},{"id":10752,"name":"War"},{"id":37,"name":"Western"}]})";
            Json::Value data;
            Json::CharReaderBuilder builder;
            std::istringstream iss(json_str);
            std::string errs;
            Json::parseFromStream(builder, iss, &data, &errs);
            return data;
        }

        Json::Value get_tv() {
            std::string json_str = R"({"genres":[{"id":10759,"name":"Action & Adventure"},{"id":16,"name":"Animation"},{"id":35,"name":"Comedy"},{"id":80,"name":"Crime"},{"id":99,"name":"Documentary"},{"id":18,"name":"Drama"},{"id":10751,"name":"Family"},{"id":10762,"name":"Kids"},{"id":9648,"name":"Mystery"},{"id":10763,"name":"News"},{"id":10764,"name":"Reality"},{"id":10765,"name":"Sci-Fi & Fantasy"},{"id":10766,"name":"Soap"},{"id":10767,"name":"Talk"},{"id":10768,"name":"War & Politics"},{"id":37,"name":"Western"}]})";
            Json::Value data;
            Json::CharReaderBuilder builder;
            std::istringstream iss(json_str);
            std::string errs;
            Json::parseFromStream(builder, iss, &data, &errs);
            return data;
        }
    };

    struct Database {
        Json::Value get(const std::string& type, int page) {
            std::string url = "https://api.themoviedb.org/3/discover/" + type + "?api_key=" + ApiKey + "&with_origin_region=US&language=en-US&region=US&page=" + std::to_string(page);
            std::string response = httpGet(url);

            Json::Value data;
            Json::CharReaderBuilder builder;
            std::istringstream iss(response);
            std::string errs;
            Json::parseFromStream(builder, iss, &data, &errs);
            return data;
        }

        Json::Value get_genre(const std::string& type, int page, int genre_id) {
            std::string url = "https://api.themoviedb.org/3/discover/" + type + "?api_key=" + ApiKey + "&with_origin_region=US&language=en-US&region=US&page=" + std::to_string(page) + "&with_genres=" + std::to_string(genre_id);
            std::string response = httpGet(url);

            Json::Value data;
            Json::CharReaderBuilder builder;
            std::istringstream iss(response);
            std::string errs;
            Json::parseFromStream(builder, iss, &data, &errs);
            return data;
        }

        Json::Value search(const std::string& query, const std::string& type, int page) {
            std::string url = "https://api.themoviedb.org/3/search/" + type + "?api_key=" + ApiKey + "&with_origin_region=US&language=en-US&region=US&query=" + query + "&page=" + std::to_string(page);
            std::string response = httpGet(url);

            Json::Value data;
            Json::CharReaderBuilder builder;
            std::istringstream iss(response);
            std::string errs;
            Json::parseFromStream(builder, iss, &data, &errs);
            return data;
        }
    };

    Genre genre;
    Database database;

    std::string get(const std::string& type, const std::string& id) {
        return Link + "embed/" + type + "/" + id;
    }

    Json::Value details(const std::string& type, const std::string& id) {
        std::string url = "https://api.themoviedb.org/3/" + type + "/" + id + "?api_key=" + ApiKey + "&language=en-US";
        std::string response = httpGet(url);

        Json::Value data;
        Json::CharReaderBuilder builder;
        std::istringstream iss(response);
        std::string errs;
        Json::parseFromStream(builder, iss, &data, &errs);
        return data;
    }

    Json::Value recommended(const std::string& type, const std::string& id) {
        std::string url = "https://api.themoviedb.org/3/" + type + "/" + id + "/recommendations?api_key=" + ApiKey + "&language=en-US";
        std::string response = httpGet(url);

        Json::Value data;
        Json::CharReaderBuilder builder;
        std::istringstream iss(response);
        std::string errs;
        Json::parseFromStream(builder, iss, &data, &errs);
        return data;
    }
};
