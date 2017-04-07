using System;
using System.Linq;

namespace SumTo13
{
    class Program
    {
        public static void Main()
        {
            var nums = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();

            if (nums[0] + nums[1] + nums[2] == 13 ||
                -nums[0] + nums[1] + nums[2] == 13 ||
                -nums[0] - nums[1] + nums[2] == 13 ||
                -nums[0] - nums[1] - nums[2] == 13 ||
                -nums[0] + nums[1] - nums[2] == 13 ||
                nums[0] + nums[1] - nums[2] == 13 ||
                nums[0] - nums[1] + nums[2] == 13 ||
                nums[0] - nums[1] - nums[2] == 13)
            {
                Console.WriteLine("Yes");
            }
            else Console.WriteLine("No");
        }
    }
}
