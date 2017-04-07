using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace HashCode_2017
{
    public class Cache
    {
        public int Memory { get; set; }
        public Dictionary<Endpoint, int> Connections { get; set; }
        public List<int> Videos { get; set; }


        public Cache(int memory)
        {
            Memory = memory;
            Connections = new Dictionary<Endpoint, int>();
            Videos = new List<int>();
        }
    }

    public class Endpoint
    {
        public int LatencyToMain { get; set; }
        public Dictionary<Cache, int> CasheConnections { get; set; }
        public Dictionary<int, int> Videos { get; set; }


        public Endpoint(int latency)
        {
            LatencyToMain = latency;
            CasheConnections = new Dictionary<Cache, int>();
            Videos= new Dictionary<int, int>();
        }

        public void RemoveVideo(int video)
        {
            if(Videos.ContainsKey(video))
                Videos.Remove(video);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var txt = File.ReadAllLines(@"videos_worth_spreading.txt");
            var inputRow = 0;

            var row1 = txt[inputRow++].Split(' ').Select(int.Parse).ToArray();

            int videosCount = row1[0];
            int endpointsCount = row1[1];
            int descriptionsCount = row1[2];
            int cashesCount = row1[3];
            int capacity = row1[4];

            var videos = txt[inputRow++].Split(' ').Select(int.Parse).ToList();

            var caches = new List<Cache>();
            for (int i = 0; i < cashesCount; i++)
            {
                caches.Add(new Cache(capacity));
            }

            var endpoints = new List<Endpoint>();

            for (int i = 0; i < endpointsCount; i++)
            {
                var currInput = txt[inputRow++].Split(' ').Select(int.Parse).ToList();
                var currEndpoint = new Endpoint(currInput[0]);

                for (int u = 0; u < currInput[1]; u++)
                {
                    var innerInput = txt[inputRow++].Split(' ').Select(int.Parse).ToList();
                    currEndpoint.CasheConnections.Add(caches[innerInput[0]], innerInput[1]);
                    caches[innerInput[0]].Connections.Add(currEndpoint, innerInput[1]);
                }

                endpoints.Add(currEndpoint);
            }

            for (int i = 0; i < descriptionsCount; i++)
            {
                var lineInput = txt[inputRow++].Split(' ').Select(int.Parse).ToList();
                if (endpoints[lineInput[1]].Videos.ContainsKey(lineInput[0]))
                {
                    endpoints[lineInput[1]].Videos[lineInput[0]] += lineInput[2];
                }
                else
                {
                    endpoints[lineInput[1]].Videos.Add(lineInput[0], lineInput[2]);
                }
                
            }

            foreach (var cache in caches.OrderBy(cache => cache.Connections.Count).ToList())
            {
                var videorequests = new Dictionary<int, int>();

                foreach (var endpoint in cache.Connections.Keys)
                {
                    foreach (var video in endpoint.Videos)
                    {
                        if (videorequests.ContainsKey(video.Key))
                        {
                            videorequests[video.Key] += video.Value;
                        }
                        else
                        {
                            videorequests.Add(video.Key, video.Value);
                        }
                    }
                }

                foreach (var video in videorequests.OrderBy(video => video.Value))
                {
                    if (cache.Memory < videos[video.Key]) continue;

                    cache.Videos.Add(video.Key);
                    cache.Memory -= videos[video.Key];

                    foreach (var endpoint in cache.Connections.Keys)
                    {
                        endpoint.RemoveVideo(video.Key);
                    }
                }
            }

            var text = "";
            int outputCount = 0;

            foreach (var cache in caches)
            {
                if (cache.Videos.Count != 0)
                {
                    outputCount++;
                    var currentString = caches.IndexOf(cache)+" ";
                    foreach (var video in cache.Videos)
                    {
                        currentString += video+" ";
                    }
                    text+=currentString+System.Environment.NewLine;
                }
            }

            var output = outputCount + System.Environment.NewLine + text;
            
            File.WriteAllText(@"videos.txt", output);
        }
    }
}
