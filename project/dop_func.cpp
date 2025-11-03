#include "project.h"

void matini(int q[], int l)
{
    for (int i = 0; i < l; i++)
    {
        q[i] = 0;
    }
}

int max(int i1, int i2)
{
    if (i1 > i2)
    {
        return i1;
    }
    return i2;
}
int max(int i1, int i2, int i3)
{
    if (max(i1, i2) < i3)
    {
        return i3;
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i4)
{
    if (max(i1, i2) < max(i3, i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2);
}
int max(int i1, int i2, int i3, int i4, int i5)
{
    if (max(i1, i2, i5) < max(i3, i4))
    {
        return max(i3, i4);
    }
    return max(i1, i2, i5);
}
int min(int q[10])
{
    int rez = 0;
    for (int i = 1; i < 10; i++)
    {
        rez = q[rez] > q[i] ? q[i] : rez;
    }
    return rez;

}
int min(int q[], int porog)
{
    int rez = 0;
    for (int i = 1; i < 10; i++)
    {
        rez = ((q[rez] > q[i]) && (q[i] > porog) || (q[rez] <= porog)) ? q[i] : rez;
    }
    return rez;
}