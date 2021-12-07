#include <algorithm>
#include <iostream>
using namespace std;

void println(long long* arr,long long size)
{
    cout << "line: ";
    for (long long i = 0; i < size; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

void merge_z(long long *p, long long *z, long long *temp, long long start, long long mid, long long end)
{
    // crawlers for both intervals and for temp
    long long i = start, j = mid + 1, k = 0;

    // traverse both arrays and in each iteration add smaller of both elements in temp
    while (i <= mid && j <= end)
    {
        if (z[i] <= z[j])
        {
            temp[k++] = z[i];
            temp[k++] = p[i];
            i++;
        }
        //*(P[i]) > *(P[j])
        else
        {
            temp[k++] = z[j];
            temp[k++] = p[j];
            j++;
        }
    }

    // add elements left in the first interval
    while (i <= mid)
    {
        temp[k++] = z[i];
        temp[k++] = p[i];
        i++;
    }

    // add elements left in the second interval
    while (j <= end)
    {
        temp[k++] = z[j];
        temp[k++] = p[j];
        j++;
    }
    for (k = start; k <= end; k++)
    {
        z[k] = temp[2 * (k - start)];
        p[k] = temp[2 * (k - start) + 1];
    }
}

void merge_sort_z(long long *p, long long *z, long long *temp, long long start, long long end)
{
    if (start < end)
    {
        long long mid = (start + end) / 2;
        merge_sort_z(p, z, temp, start, mid);
        merge_sort_z(p, z, temp, mid + 1, end);
        merge_z(p, z, temp, start, mid, end);
    }
}

long long int merge_p(long long *p, long long *z, long long *temp, long long start, long long mid, long long end, int found_mid, long long a, long long b, long long c,long long n)
{
    long long i = start, j = mid + 1, k = 0;
    long long int inv_count = 0;
    long long int total_inv_count = 0;
    if (found_mid)
    {
        while (i <= mid && j <= end)
        {
            // cout << "i: " << i << ","<< (p[i]) << endl;
            // cout << "j: "<< j << ", " <<p[j] << endl;
            if (b  * p[i] + c  <  p[j] * a)
            {
                i++;
                inv_count++;

            }
            else
            {
                j++;
                total_inv_count += inv_count;

            }
        }
        while (j <= end)
        {
            j++;
            total_inv_count += inv_count;
        }
    }
    else
    {
        total_inv_count = 0;
    }

    // sort p
    i = start;
    j = mid + 1;
    k = 0;
    while (i <= mid && j <= end)
    {
        // caution <= or = 
        if (p[i] < p[j])
        {
            temp[k] = p[i];
            k++;
            i++;
        }

        else
        {
            temp[k] = p[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
        temp[k++] = p[i++];

    while (j <= end)
        temp[k++] = p[j++];

    for ( i = 0; i < (end-start + 1); i++)
    {
        p[start + i] = temp[i];
    }
    // println(p, n);
    return total_inv_count;
}

long long int merge_sort_p(long long *p, long long *z, long long *temp, long long start, long long end, long long a, long long b, long long c,long long n)
{
    long long mid = 0;
    long long int inv_count = 0;
    if (end > start)
    {
        int found_mid = 0;
        mid = (start + end) / 2;
        if (z[mid] != z[mid + 1])
            found_mid = 1;
        while (found_mid == 0)
        {


            mid++;
            if (mid == end)
                break;
            if (z[mid] != z[mid + 1])
                found_mid = 1;
            // no boundary in back

        }
        if (found_mid == 0)
        {
            mid = (start + end) / 2;
            if (z[mid] != z[mid + 1])
                found_mid = 1;
            while (found_mid == 0)
            {
                if (mid == start)
                    break;
                mid--;

                if (z[mid] != z[mid + 1])
                    found_mid = 1;
            }
        }

        if (found_mid == 0)
            mid = (start + end) / 2;

        inv_count += merge_sort_p(p , z, temp, start, mid, a, b, c,n);
        inv_count += merge_sort_p(p, z, temp, mid + 1, end, a, b, c,n);
        inv_count += merge_p(p, z, temp, start, mid, end, found_mid, a, b, c,n);
    }
    return inv_count;
}


int main()
{
    long long n;
    long long a, b, c;
    cin >> n;
    cin >> a >> b >> c;

    long long *p = new long long[2000000];
    long long *z = new long long[2000000];

    long long *temp = new long long[4000000];
    for (long long i = 0; i < n; i++)
    {
        cin >> p[i];
        cin >> z[i];
    }
    //sort z
    merge_sort_z(p, z, temp, 0, n - 1);
    // println(p, n);
    // println(z, n);
    long long int ans;
    ans = merge_sort_p(p, z, temp, 0, n - 1, a, b, c,n);

    cout << ans << endl;

    return 0;
}
