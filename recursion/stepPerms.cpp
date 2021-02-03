#include <bits/stdc++.h>

using namespace std;

// n will be the number of steps left. At every stage, call recursively this function with each possible step climbing 
// technique, exploring all options, and add up the successful runs. Only if we manage to exactly hit the top step 
// will the solution be considered valid and added to the total.
int stepPerms(int n) {
	if (n < 0) return 0; // Fail
	if (n == 0) return 1; // Success

	return (stepPerms(n - 1) + stepPerms(n - 2) + stepPerms(n - 3))%10000000007; // Get total from all possibles strategies starting from this step
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < s; s_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int res = stepPerms(n);

        fout << res << "\n";
    }

    fout.close();
    return 0;
}
