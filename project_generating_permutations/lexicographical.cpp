#include <string>
#include <iostream>

// This method is the standard implementation of QuickSort
int QuicksortDivide(std::string &data, int left, int right){
	// start with elements to either end of the data
	int i = left;
	int j = right - 1;
	// chose a pivot element
	char pivot = data[right];
	// don't let the indices form left and right cross positions
	while(i < j){
		// move right index along to find element that is smaller than pivot
		while(data[i] < pivot && i < right - 1){
			i++;
		}
		// move left index along to find element that is bigger than pivot
		while(data[j] >= pivot && j > left){
			j--;
		}
		// if the elements are out of order, switch them
		if(i < j){
			char temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}
	// set pivot element to right place and return its position
	if(data[i] >= pivot){
		char temp = data[i];
		data[i] = data[right];
		data[right] = temp;
		return i;
	} else{
		return right;
	}
}

// This method is the standard implementation of QuickSort
void Quicksort(std::string &data, int left, int right){
	// as long as the list isn't finished sorting, divide into two parts and sort them recursively
	if(left < right){
		int pivot = QuicksortDivide(data, left, right);
		Quicksort(data, left, pivot - 1);
		Quicksort(data, pivot + 1, right);
	}
}

// Generates a combination of a certain length in natural order
std::string FirstCombination(int length){
	std::string combination;
	// append the numbers in ascending order
	for(int i = 1; i <= length; i++){
		combination += std::to_string(i);
	}
	return combination;
}

// Finds the next combination in lexicographical order
// Note that the string is passed by reference. Thus, the function can return a boolean for wether or not there
// is a next combination.
bool NextCombination(std::string &combination){
	// find last position with digit size smaller than the maximum for that position
	int n = combination.length();
	int k = 0;
	do{
		k++;
		// the - '0' converts the char into an int, as numbers start at position 48 in ASCII
	} while(k <= n && combination[n - k] - '0' == 10 - k);
	// if none found, the combination is the last one
	if(k == n + 1){
		return false;
		// else, increase the digit at the position by one and modify the suffix
	} else{
		// note the use of the preincrement
		int start_of_suffix = ++combination[n - k];
		for(int j = n - k + 1; j < n; j++){
			// note the use of the preincrement
			combination[j] = ++start_of_suffix;
		}
		return true;
	}
}

// Finds the next permutation in lexicographical order
// Note that the string is passed by reference. Thus, the function can return a boolean for wether or not there
// is a next permutation.
bool NextPermutation(std::string &permutation){
	int n = permutation.length();
	int k = 1;
	char prev_digit;
	// search for the first descending digit from the right
	do{
		prev_digit = permutation[n - k++];
	} while(k <= n && permutation[n - k] > prev_digit);
	// if no descending element found, there is no next permutation
	if(k == n + 1){
		return false;
		// else generate the next permutation
	} else{
		// cycle through all previous digits and find the smallest that is larger than the current one
		char digit = permutation[n - k];
		char swap_digit = '9';
		int swap_digit_pos = 0;
		for(int i = n - k + 1; i < n; i++){
			if(permutation[i] > digit && permutation[i] <= swap_digit){
				swap_digit = permutation[i];
				swap_digit_pos = i;
			}
		}
		// swap the digits
		permutation[n - k] = swap_digit;
		permutation[swap_digit_pos] = digit;
		// sort the suffix
		if(k > 2){
			Quicksort(permutation, n - k + 1, n - 1);
		}
		return true;
	}
}


void GenerateLexicographical(int length, bool print){
	std::string combination = FirstCombination(length);
	// generate all combinations
	do{
		std::string permutation = combination;
		// generate all permutations
		do{
			// print
			if(print){
				std::cout << permutation << std::endl;
			}
		} while(NextPermutation(permutation));
	} while(NextCombination(combination));
	// give output
	std::cout << "Finished!" << std::endl;
}