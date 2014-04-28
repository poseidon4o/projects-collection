using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;

namespace _20
{
	class Program
	{
		static void Main(string[] args)
		{
			BigInteger a = 1;
			for(int c = 1; c < 100; c++) a *= c;
			int sum = 0;
			Console.WriteLine(a);
			while( a > 0 ){
				sum += (int) (a % 10);
				a /= 10;
			}
			Console.WriteLine(sum);
			Console.Read();
		}
	}
}
