#include "api.hpp"

// THIS WILL NOT WORK, find a way to get a query maybe by input or any other type of way like maybe an input then SET the query key thing directly

int main() {
    std::cout << "Auto's Free Movie API v1" << std::endl;

    std::string type = Query["type"];
    std::string id = Query["id"];

    AFMA afma;

    if (type.empty() && id.empty()) {
        afma.genre.get_movie();
        afma.genre.get_tv();
    } else {
        afma.get(type, id);
        afma.details(type, id);
        afma.recommended(type, id);
    }

    return 0;
}
