// auto's free movie api

const Link = "https://vidsrc.me/"; // If you want to be unblocked at school use vidsrc.pm
const Query = new URLSearchParams(); // To get params
const Type = Query.get("type").toLowerCase() || null; // "Movie" or "TV"
const Id = Query.get("id") || null; // Movie Id or Tv Show from IMDB/or TMDB
const ApiKey = ""; // Include an API Key if your using TMDB/or Edit the code for IMDB
let afma = {}; // api

console.log("Auto's Free Movie API v1");
console.log("")

if (Type == null && Id == null) {
    // API functions for your homepage

    afma = {
        genre = {
            get_movie = function () {
                return JSON.parse(`{"genres":[{"id":28,"name":"Action"},{"id":12,"name":"Adventure"},{"id":16,"name":"Animation"},{"id":35,"name":"Comedy"},{"id":80,"name":"Crime"},{"id":99,"name":"Documentary"},{"id":18,"name":"Drama"},{"id":10751,"name":"Family"},{"id":14,"name":"Fantasy"},{"id":36,"name":"History"},{"id":27,"name":"Horror"},{"id":10402,"name":"Music"},{"id":9648,"name":"Mystery"},{"id":10749,"name":"Romance"},{"id":878,"name":"Science Fiction"},{"id":10770,"name":"TV Movie"},{"id":53,"name":"Thriller"},{"id":10752,"name":"War"},{"id":37,"name":"Western"}]}`);
            },
            get_tv = function () {
                return JSON.parse(`{"genres":[{"id":10759,"name":"Action & Adventure"},{"id":16,"name":"Animation"},{"id":35,"name":"Comedy"},{"id":80,"name":"Crime"},{"id":99,"name":"Documentary"},{"id":18,"name":"Drama"},{"id":10751,"name":"Family"},{"id":10762,"name":"Kids"},{"id":9648,"name":"Mystery"},{"id":10763,"name":"News"},{"id":10764,"name":"Reality"},{"id":10765,"name":"Sci-Fi & Fantasy"},{"id":10766,"name":"Soap"},{"id":10767,"name":"Talk"},{"id":10768,"name":"War & Politics"},{"id":37,"name":"Western"}]}`);
            }
        },
        database = {
            get = function (type, page) {
                fetch(`https://api.themoviedb.org/3/discover/${type.toLowerCase()}?api_key=${ApiKey}&with_origin_region=US&language=en-US&region=US&page=${page}`)
                .then(Response => Response.json())
                .then(Data => {
                    return Data;
                })
                .catch(Rejected => {
                    return Data; // TMDB always returns an error
                });
            },
            get_genre = function(type, page, genre_id) {
                fetch(`https://api.themoviedb.org/3/discover/${type.toLowerCase()}?api_key=${ApiKey}&with_origin_region=en-US&language=en-US&region=US&page=${page}&with_genres=${genre_id}`)
                .then(Response => Response.json())
                .then(Data => {
                    return Data;
                })
                .catch(Rejected => {
                    return Data;
                });
            },
            search = function (query, type, page) {
                fetch(`https://api.themoviedb.org/3/search/${type.toLowerCase()}?api_key=${ApiKey}&with_origin_region=US&language=en-US&region=US&query=${query}&page=${page}`)
                .then(Response => Response.json())
                .then(Data => {
                    return Data;
                })
                .catch(Rejected => {
                    return Data;
                });
            }
        }
    };
} else {
    // Link Getter

    afma = {
        get = function(type, id) {
            return `${Link}/embed/${type.toLowerCase}/${id}`;
        },
        details = function(type, id) {
            fetch(`https://api.themoviedb.org/3/${type.toLowerCase()}/${id}?api_key=${ApiKey}&language=en-US`)
            .then(Response => Response.json())
            .then(Data => {
                return Data;
            })
            .catch(Rejected => {
                return Data;
            });
        },
        recommended = function(type, id) {
            fetch(`https://api.themoviedb.org/3/${type.toLowerCase()}/${id}/recommendations?api_key=${ApiKey}&language=en-US`)
            .then(Response => Response.json())
            .then(Data => {
                return Data;
            })
            .catch(Rejected => {
                return Data;
            });
        }
    };
}
