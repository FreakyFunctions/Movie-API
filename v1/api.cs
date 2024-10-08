using System;
using System.Net.Http;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;

class Program
{
    static string Link = "https://vidsrc.me/";
    static string ApiKey = "";

    static async Task<string> HttpGet(string url)
    {
        using (HttpClient client = new HttpClient())
        {
            HttpResponseMessage response = await client.GetAsync(url);
            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadAsStringAsync();
            }
            return null;
        }
    }

    class AFMA
    {
        public class Genre
        {
            public JObject GetMovie()
            {
                string jsonStr = @"{
                    'genres': [
                        {'id': 28, 'name': 'Action'},
                        {'id': 12, 'name': 'Adventure'},
                        {'id': 16, 'name': 'Animation'},
                        {'id': 35, 'name': 'Comedy'},
                        {'id': 80, 'name': 'Crime'},
                        {'id': 99, 'name': 'Documentary'},
                        {'id': 18, 'name': 'Drama'},
                        {'id': 10751, 'name': 'Family'},
                        {'id': 14, 'name': 'Fantasy'},
                        {'id': 36, 'name': 'History'},
                        {'id': 27, 'name': 'Horror'},
                        {'id': 10402, 'name': 'Music'},
                        {'id': 9648, 'name': 'Mystery'},
                        {'id': 10749, 'name': 'Romance'},
                        {'id': 878, 'name': 'Science Fiction'},
                        {'id': 10770, 'name': 'TV Movie'},
                        {'id': 53, 'name': 'Thriller'},
                        {'id': 10752, 'name': 'War'},
                        {'id': 37, 'name': 'Western'}
                    ]
                }";
                return JObject.Parse(jsonStr);
            }

            public JObject GetTv()
            {
                string jsonStr = @"{
                    'genres': [
                        {'id': 10759, 'name': 'Action & Adventure'},
                        {'id': 16, 'name': 'Animation'},
                        {'id': 35, 'name': 'Comedy'},
                        {'id': 80, 'name': 'Crime'},
                        {'id': 99, 'name': 'Documentary'},
                        {'id': 18, 'name': 'Drama'},
                        {'id': 10751, 'name': 'Family'},
                        {'id': 10762, 'name': 'Kids'},
                        {'id': 9648, 'name': 'Mystery'},
                        {'id': 10763, 'name': 'News'},
                        {'id': 10764, 'name': 'Reality'},
                        {'id': 10765, 'name': 'Sci-Fi & Fantasy'},
                        {'id': 10766, 'name': 'Soap'},
                        {'id': 10767, 'name': 'Talk'},
                        {'id': 10768, 'name': 'War & Politics'},
                        {'id': 37, 'name': 'Western'}
                    ]
                }";
                return JObject.Parse(jsonStr);
            }
        }

        public class Database
        {
            public async Task<JObject> Get(string type, int page)
            {
                string url = $"https://api.themoviedb.org/3/discover/{type}?api_key={ApiKey}&with_origin_region=US&language=en-US&region=US&page={page}";
                string response = await HttpGet(url);
                if (response != null)
                {
                    return JObject.Parse(response);
                }
                return null;
            }

            public async Task<JObject> GetGenre(string type, int page, int genreId)
            {
                string url = $"https://api.themoviedb.org/3/discover/{type}?api_key={ApiKey}&with_origin_region=US&language=en-US&region=US&page={page}&with_genres={genreId}";
                string response = await HttpGet(url);
                if (response != null)
                {
                    return JObject.Parse(response);
                }
                return null;
            }

            public async Task<JObject> Search(string query, string type, int page)
            {
                string url = $"https://api.themoviedb.org/3/search/{type}?api_key={ApiKey}&with_origin_region=US&language=en-US&region=US&query={query}&page={page}";
                string response = await HttpGet(url);
                if (response != null)
                {
                    return JObject.Parse(response);
                }
                return null;
            }
        }

        public Genre genre = new Genre();
        public Database database = new Database();

        public string Get(string type, string id)
        {
            return $"{Link}/embed/{type}/{id}";
        }

        public async Task<JObject> Details(string type, string id)
        {
            string url = $"https://api.themoviedb.org/3/{type}/{id}?api_key={ApiKey}&language=en-US";
            string response = await HttpGet(url);
            if (response != null)
            {
                return JObject.Parse(response);
            }
            return null;
        }

        public async Task<JObject> Recommended(string type, string id)
        {
            string url = $"https://api.themoviedb.org/3/{type}/{id}/recommendations?api_key={ApiKey}&language=en-US";
            string response = await HttpGet(url);
            if (response != null)
            {
                return JObject.Parse(response);
            }
            return null;
        }
    }
}
