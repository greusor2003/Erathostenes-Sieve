#include <iostream>
#include <fstream>
//#include <functional>
#include <vector>
//#include <algorithm>
#include <cmath>
#include <cstdlib>

using std::vector;
using std::cout;

const uint_fast32_t MAXN = 102400; 
//hardcoded for stack size = 8192 K; set smaller for smaller stack sizes

struct Sieve 
//defining object holding primes up to n
{
	Sieve() : s(2, 1) { s[1] = 2; }
	
	Sieve(uint_fast32_t);
	
	void print() const;
        // prints sieve to console
	
	void print_tof() const;
	// prints sieve to file

	void operator()(int n);
	// generates the primes <= n; recursive implementation; depends on stack size
        
	auto get_num_primes() const { return s.size();}

	private:
		vector<int> s; //stores the primes
};


Sieve::Sieve(uint_fast32_t N)
{
	Sieve S = Sieve();
	if (N > MAXN)
	{
		auto K = N / MAXN;
		auto r = N % MAXN;
		
        for (uint_fast32_t i = 1; i <=K; i++)
			S(i*MAXN);
		if (r > 0)
		    S(N);
	}
	else S(N);
	this->s = S.s;
}

void Sieve::print() const
{
	for (auto x : s)
		cout << x << " ";
	cout << "\n";
}

void Sieve::print_tof() const
{
  std::ofstream output("Sift_primes.txt");
  if (output.fail())
	{
		cout << "Error opening file";
		exit(1);
	}
  for (auto p : s) 
      output << std::to_string(p) << " ";
  output.close();
}

void Sieve::operator()(int n)
{
		
	auto last = *(s.cend()-1);
	
	if (n > last)
	{
		operator()(n-1);
	}
	auto i = 1;
	for (; s[i] <= sqrt(n+1); i++ )
		if ((n+1) % s[i] == 0)
			break;
	if (s[i] > sqrt(n+1))
		s.push_back(n+1);
	
}
/********************************************************************/
int main()
{
	
	uint_fast32_t N;
	std::cout << "positive integer > 1: ";
	std::cin >> N;
	std::cout << "\n";
	Sieve S = Sieve(N);

  	S.print_tof();
	cout << "there are " << S.get_num_primes() << " primes less than or equal to " << N << "\n";

	return 0;	
}
