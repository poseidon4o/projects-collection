using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _26
{
	class Program
	{
		static void Main(string[] args)
		{
			double a;
			int bLen = -1;
			for(int c = 1; c < 1000; c++){
				a = 1/c;
				int tLen = Program.SecLen(a.ToString());
				if(tLen > bLen) bLen = tLen;
			}
			Console.WriteLine(bLen);
			Console.Read();
		}

		static public int SecLen(string a){
			a.
		}
	}
}
