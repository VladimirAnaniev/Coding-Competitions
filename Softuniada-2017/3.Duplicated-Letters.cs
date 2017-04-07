using System;

namespace DuplicatedLetters
{
    class Program
    {
        public static void Main()
        {
            var s = Console.ReadLine();

            var operations = 0;

            while (true)
            {
                var stop = true;
                for (var i = 0; i < s.Length-1; i++)
                {
                    if (s[i] != s[i + 1]) continue;
                    s = s.Remove(i, 2);
                    operations++;
                    stop = false;
                }

                if (stop) break;
            }

            Console.WriteLine(s.Length > 0 ? s : "Empty String");
            Console.WriteLine(operations+ " operations");
        }
    }
}
