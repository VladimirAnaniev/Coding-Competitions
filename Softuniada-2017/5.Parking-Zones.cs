using System;
using System.Collections.Generic;
using System.Linq;

namespace ParkZones
{
    internal class Program
    {
        public static void Main()
        {
            var zones = new List<Zone>();
            var freeCells = new List<Cell>();

            var n = int.Parse(Console.ReadLine());

            for (int i = 0; i < n; i++)
            {
                var input = Console.ReadLine().Split(':');
                var name = input[0];
                var inputParts = input[1].Split(',').ToArray();

                zones.Add(new Zone(name, int.Parse(inputParts[0]), int.Parse(inputParts[1]),
                    int.Parse(inputParts[2]), int.Parse(inputParts[3]), double.Parse(inputParts[4])));

            }

            var freeSpots = Console.ReadLine().Split(';');

            foreach (var spot in freeSpots)
            {
                var coordinates =
                    spot.Split(',').Select(int.Parse).ToArray();

                var current = new Cell(coordinates[0], coordinates[1]);

                foreach (var zone in zones)
                {
                    if (zone.CellIsInside(current))
                    {
                        current.Zone = zone;
                        break;
                    }
                }

                freeCells.Add(current);
            }

            var targetCoordinates = Console.ReadLine()
                    .Split(new[] {' ', ','}, StringSplitOptions.RemoveEmptyEntries)
                    .Select(int.Parse).ToArray();
            var target = new Cell(targetCoordinates[0], targetCoordinates[1]);

            int time = int.Parse(Console.ReadLine());

            var prices = new Dictionary<Cell, double>();
            foreach (var spot in freeCells)
            {
                var price = Math.Ceiling(spot.DistanceFrom(target) * 2 * time / 60.0) * spot.Zone.Price;
                prices.Add(spot, price);
            }

            var sorted = prices.OrderBy(pair => pair.Value).ThenBy(pair => pair.Key.DistanceFrom(target));
            var optimal = sorted.ElementAt(0);
            Console.WriteLine("Zone Type: {0}; X: {1}; Y: {2}; Price: {3:f2}", optimal.Key.Zone.Name, optimal.Key.X, optimal.Key.Y, optimal.Value);
        }
    }

    internal class Cell
    {
        public Zone Zone { get; set; }
        public int X { get; set; }
        public int Y { get; set; }

        public Cell(int x, int y)
        {
            this.X = x;
            this.Y = y;
        }

        public int DistanceFrom(Cell c)
        {
            return Math.Abs(this.X - c.X) + Math.Abs(this.Y - c.Y) - 1;
        }
    }

    internal class Zone
    {
        public string Name { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public double Price { get; set; }

        public Zone(string name,int x, int y, int width, int height, double price)
        {
            this.Name = name;
            this.X = x;
            this.Y = y;
            this.Width = width;
            this.Height = height;
            this.Price = price;
        }

        public bool CellIsInside(Cell c)
        {
            return c.X >= this.X && c.X < this.X + this.Width && c.Y >= this.Y && c.Y < this.Y + this.Height;
        }

    }
}
