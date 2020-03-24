#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>


using namespace std;

int kthSort(vector<int>& arr, int l, int r, int k) {
	int avg = (l + r) / 2;
	int kk = arr[avg];
	int i = l, j = r;
	while (i <= j) {
		while (arr[i] < kk) {
			i++;
		}
		while (arr[j] > kk) {
			j--;
		}
		if (i <= j) {
			swap(arr[i], arr[j]);
			i += 1;
			j -= 1;
		}
	}
	if (l <= k && k <= j) {
		return kthSort(arr, l, j, k);
	}
	if (i <= k && k <= r) {
		return kthSort(arr, i, r, k);
	}
	return arr[k];
}
int main() {
	ifstream fin("kth.in");
	ofstream fout("kth.out");
	int n, k, a, b, c;
	fin >> n >> k >> a >> b >> c;
	k--;
	vector<int>arr(n);
	for (int i = 0; i < 2; i++) {
		fin >> arr[i];
	}
	for (int i = 2; i < n; i++) {
		arr[i] = arr[i - 2] * a + arr[i - 1] * b + c;
	}
	int ans = kthSort(arr, 0, n - 1, k);
	fout << ans;
	fin.close();
	fout.close();
	return 0;
}