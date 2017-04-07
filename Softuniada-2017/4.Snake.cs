using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Remoting.Channels;
using System.Text;
using System.Threading.Tasks;

namespace _4.Snake
{
    class Program
    {
        public static int[] snakePosition = new int[3];
        private static int n;


        static void Main(string[] args)
        {
            n = int.Parse(Console.ReadLine());

            char[][][] cube = createCube(n);
            int points = 0;


            for (int i = 0; i < n; i++)
            {
                var layers = Console.ReadLine().Split(new [] {' ', '|'}, StringSplitOptions.RemoveEmptyEntries).ToArray();

                for (int u = 0; u < n; u++)
                {
                    var chars = layers[u];

                    for (int j = 0; j < n; j++)
                    {
                        if (chars[j] == 's')
                        {
                            snakePosition[0] = u;
                            snakePosition[1] = i;
                            snakePosition[2] = j;
                        }
                        cube[u][i][j] = chars[j];
                    }
                }
            }

            bool dead = false;
            string direction = Console.ReadLine();
            while (true)
            {
                var next = Console.ReadLine().Split(' ').ToArray();
                string nextDirection = next[0];
                int steps = int.Parse(next[2]);

                int newPoints = makeMove(cube, direction, steps);

                if (newPoints >= 0) points += newPoints;
                else
                {
                    dead = true;
                    break;
                }

                direction = nextDirection;
                if (direction == "end") break;
            }

            Console.WriteLine("Points collected: "+ points);
            if(dead) Console.WriteLine("The snake dies.");

        }

        public static int makeMove(char[][][] cube, string direction, int steps)
        {
            int points = 0;
            for (int i = 0; i < steps; i++)
            {
                cube[snakePosition[0]][snakePosition[1]][snakePosition[2]] = 'o';

                if (direction == "forward")
                {
                    snakePosition[1]--;
                }
                else if (direction == "backward")
                {
                    snakePosition[1]++;
                }
                else if (direction == "down")
                {
                    snakePosition[0]++;
                }
                else if (direction == "up")
                {
                    snakePosition[0]--;
                }
                else if (direction == "left")
                {
                    snakePosition[2]--;
                }
                else if (direction == "right")
                {
                    snakePosition[2]++;
                }

                for (int j = 0; j < snakePosition.Length; j++)
                {
                    if (snakePosition[j] >= n)
                    {
                        return -1;
                    }
                }

                if (cube[snakePosition[0]][snakePosition[1]][snakePosition[2]] == 'a') points++;
                cube[snakePosition[0]][snakePosition[1]][snakePosition[2]] = 's';
            }

            return points;
        }

        public static char[][][] createCube(int n)
        {
            var cube = new char[n][][];

            for (int i = 0; i < n; i++)
            {
                var currentLayer = new char[n][];

                for (int u = 0; u < n; u++)
                {
                    var currentRow = new char[n];

                    for (int j = 0; j < n; j++)
                    {
                        currentRow[j] = ' ';
                    }

                    currentLayer[u] = currentRow;
                }

                cube[i] = currentLayer;
            }

            return cube;
        }
    }
}
