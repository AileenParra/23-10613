#include <vector>

using namespace std;

int main(){
  return 0;
}

int vectorToInt(const vector<char>& digits, int base) {
    int result = 0;
    for (size_t i = 0; i < digits.size(); i++) {
        result = result * base + (digits[i] - '0');
    }
    return result;
}

vector<char> intToVector(int n, int base) {
    if (n == 0) return {'0'};
    vector<char> result;
    bool negative = false;
    if (n < 0) {
        negative = true;
        n = -n;
    }
    while (n > 0) {
        int digit = n % base;
        result.push_back('0' + digit);
        n /= base;
    }
    if (negative) {
        result.push_back('-');
    }
    vector<char> reversed;
    for (int i = (int)result.size() - 1; i >= 0; i--) {
        reversed.push_back(result[i]);
    }
    return reversed;
}

double mean(vector<double> v){
    if (v.empty()) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    return sum / v.size();
}

double variance(vector<double> v){
    if (v.size() <= 1) return 0.0;
    double m = mean(v);
    double sumSquaredDiff = 0.0;
    for (size_t i = 0; i < v.size(); i++) {
        double diff = v[i] - m;
        sumSquaredDiff += diff * diff;
    }
    return sumSquaredDiff / (v.size() - 1);
}

double pearson_r(vector<double> A, vector<double> B){
    if (A.size() != B.size() || A.empty()) {
        return 0.0;
    }
    size_t n = A.size();
    double meanA = mean(A);
    double meanB = mean(B);
    double sumDiffA = 0.0;
    double sumDiffB = 0.0;
    double sumProductDiff = 0.0;
    for (size_t i = 0; i < n; i++) {
        double diffA = A[i] - meanA;
        double diffB = B[i] - meanB;
        sumDiffA += diffA * diffA;
        sumDiffB += diffB * diffB;
        sumProductDiff += diffA * diffB;
    }
    if (sumDiffA == 0.0 || sumDiffB == 0.0) {
        return 0.0;
    }
    double x = sumProductDiff / ((sumDiffA + sumDiffB) / 2);
    for (int i = 0; i < 10; i++) {
        x = (x + (sumDiffA * sumDiffB) / x) / 2;
    }
    return sumProductDiff / x;
}

vector<char> dec_to_septapus(int n){
    return intToVector(n, 7);
}

vector<char> dec_to_octopus(int n){
    return intToVector(n, 8);
}

vector<char> dec_to_hexakaidecapus(int n){
    return intToVector(n, 16);
}

vector<char> septapus_to_dec(vector<char> s){
    int value = vectorToInt(s, 7);
    return intToVector(value, 10);
}

vector<char> octopus_to_dec(vector<char> s){
    int value = vectorToInt(s, 8);
    return intToVector(value, 10);
}

vector<char> hexakaidecapus_to_dec(vector<char> s){
    int value = vectorToInt(s, 16);
    return intToVector(value, 10);
}

vector<char> septapus_to_octopus(vector<char> s){
    int decimal = vectorToInt(s, 7);
    return intToVector(decimal, 8);
}

vector<char> septapus_to_hexakaidecapus(vector<char> s){
    int decimal = vectorToInt(s, 7);
    return intToVector(decimal, 16);
}

vector<char> octapus_to_septapus(vector<char> s){
    int decimal = vectorToInt(s, 8);
    return intToVector(decimal, 7);
}

vector<char> octopus_to_hexakaidecapus(vector<char> s){
    int decimal = vectorToInt(s, 8);
    return intToVector(decimal, 16);
}

vector<char> hexakaidecapus_to_septapus(vector<char> s){
    int decimal = vectorToInt(s, 16);
    return intToVector(decimal, 7);
}

vector<char> hexakaidecapus_to_octopus(vector<char> s){
    int decimal = vectorToInt(s, 16);
    return intToVector(decimal, 8);
}
