#include <bits/stdc++.h> 
using namespace std;  
struct Point{
   int x, y;
}; 
Point P[200001];
  
int cmpX(Point p1, Point p2) { 
   return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);   
}

int cmpY(Point p1, Point p2){
   return (p1.y < p2.y);
}

long long dist(Point p1, Point p2){  
   return ((long long)(p1.x - p2.x)*(p1.x - p2.x) + (long long)(p1.y - p2.y)*(p1.y - p2.y));  
}  
long long bruteForce(Point P[], int n){  
   long long min = LLONG_MAX;  
   for (int i = 0; i < n; ++i)  
      for (int j = i+1; j < n; ++j)  
         if (dist(P[i], P[j]) < min)  
            min = dist(P[i], P[j]);  
   return min;  
}   
long long stripClosest(Point strip[], int size, long long d){  
   long long min = d; 
   sort(strip, strip + size, cmpY);  
   for (int i = 0; i < size; ++i)  
       for (int j = i + 1; j < i + 4 && j < size && (long long)(strip[j].y - strip[i].y)*(strip[j].y - strip[i].y) < min; ++j)  
         if (dist(strip[i],strip[j]) < min)
            min = dist(strip[i], strip[j]);  
   return min;  
}  
 
long long closestTwo(Point P[], int n){  
   if (n <= 3)  
      return bruteForce(P, n);  
   int mid = n/2;  
   Point midPoint = P[mid];  
   long long dl = closestTwo(P, mid);  
   long long dr = closestTwo(P + mid, n - mid);  
   long long d = min(dl, dr);  
   Point strip[n];  
   int strid = 0;  
   for (int i = 0; i < n; i++)  
      if ((long long)(P[i].x - midPoint.x)*(P[i].x - midPoint.x) < d)  
         strip[strid++] = P[i];  
   return min(d, stripClosest(strip, strid, d) );  
}  
long long closest(Point P[], int n){  
   sort(P, P + n, cmpX);  
   return closestTwo(P, n);  
}  
int main(){  
   int n;
   cin >> n;
   for(int i = 0; i < n; i ++)
      scanf("%d %d", &P[i].x, &P[i].y);
   long long int ans = closest(P, n);
   printf("%lld\n", -ans); 
   return 0;  
}  