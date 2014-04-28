using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Numerics;

namespace _25
{
	class Program
	{
		static void Main(string[] args)
		{
			BigInteger current = 0,p1 = 1,p2 = 2;
			int c = 3;
			while(true){
				c++;
				current = p1 + p2;
				p1 = p2;
				p2 = current;
				string a = current.ToString();
				current = 0;
				if(a.Length >= 1000){
					Console.WriteLine(c);
					Console.Read();
					break;
				}
			}

			
		}

	}
}
