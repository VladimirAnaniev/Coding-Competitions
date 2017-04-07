using System;

namespace HalloweenPumpkin
{
    class Program
    {
        public static void Main()
        {
            int n = int.Parse(Console.ReadLine());

            Console.WriteLine("{0}{1}{0}", new string('.', n-1), "_/_");
            Console.WriteLine("/{0}{1}{0}\\", new string('.', n-2), "^,^");

            for (int i = 0; i < n - 3; i++)
            {
                Console.WriteLine("|{0}|", new string('.',2*n-1));
            }

            Console.WriteLine("\\{0}{1}{0}/", new string('.', n - 2), "\\_/");
        }
    }
}
