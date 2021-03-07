// Franck Limtung
// 2020-Mar-8
// CSCI235
// msort function from Moududur Rahman
// merge function from Shanie Ho
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

//Shanie Ho
std::vector <int> merge(std::vector <int> a , std::vector<int> b){
    std::vector <int> merged;
    int tot = a.size() + b.size();
    int index = 0;
    int aIndex = 0;
    int bIndex = 0;
    while (index < tot){
        if (aIndex < a.size() && bIndex< b.size()){
            if (a.at(aIndex) < b.at(bIndex)){
                merged.push_back(a.at(aIndex));
                aIndex++;
                index ++;
            }
            else{
                merged.push_back(b.at(bIndex));
                bIndex++;
                index ++;
            }
        }
        else if (bIndex < b.size()){
            merged.push_back(b.at(bIndex));
            bIndex++;
            index ++;
        }
        else{
            merged.push_back(a.at(aIndex));
            aIndex++;
            index ++;
        }
    }
    return merged;
}


std::vector<int> msort(std::vector<int> in)
{
 // no sorting is needed; just return the array
 if (in.size() == 0 || in.size() == 1)
 {
  return in;
 }

 // test to see if elements need to be swapped and then swap
 if (in.size() == 2)
 {
  if (in[0] > in[1])
  {
   int x = in[1];
   in[1] = in[0];
   in[0] = x;
   return in;
  }
  return in;
 }

 int mid = in.size()/2;

 auto left = msort(std::vector<int>(in.begin(), in.begin()+mid));
 auto right = msort(std::vector<int>(in.begin()+mid, in.end()));

 return merge(left, right);
}

void print_vector(std::vector<int> a){
  for (auto i : a) {
    std::cout << i << ", ";
    
  }

  std::cout << "\n";
  
}

bool verifyArr(std::vector<int> first, std::vector<int> second) {
	if (first.size() != second.size()) {
		std::cout << "Error; wrong size.\n";
		return false;
	}
	for (int i = 0; i < first.size(); i++) {
		if (first[i] != second[i]) {
			std::cout << "Error; wrong element.\n";
			return false;
		}
	}

	return true;
}

int main()
{
	srand(time(NULL));
	
	std::cout << "Verifying algorithms...\n";
	
	for (int i = 0; i < 1000; i++) {
		for (int i = 0; i < 100; i++) {
			std::vector<int> unsorted(i);
			for(int i2=0;i2<i;i2++){
				unsorted[i2] = rand()%1000;    
			}
			//std::cout << "Unsorted: ";
			//print_vector(unsorted);
			//std::cout << "\n";
			std::vector<int> unsorted2 = unsorted;
	
			std::vector<int> sorted = msort(unsorted);
			std::sort(unsorted2.begin(), unsorted2.end());
			std::vector<int>& sortedTested = unsorted2;
			//std::cout << "Sorted: ";
			//print_vector(sorted);
	
			if (verifyArr(sorted, sortedTested) == false) {
				std::cout << "Failed test.\n";
				return 0;
			}
			
			//std::cout << "\n";
		}
	}

	std::cout << "Algorithms verified.\n";
  
	return 0;
}
