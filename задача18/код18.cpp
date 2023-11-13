using System;
using System.Management.Instrumentation;
using System.Text.RegularExpressions;
class SegmentTree
{
    private int[] t;
    private int[] array;
    private int size;

    public SegmentTree(int[] input)
    {
        array = input;
        size = input.Length;
        t = new int[4 * size];
        build(0, 0, size - 1);
    }

    public void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            t[v] = array[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2 + 1, tl, tm);
        build(v * 2 + 2, tm + 1, tr);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }

    public int GetSum(int l, int r)
    {
        return GetSumUses(0, 0, size - 1, l, r);
    }

    private int GetSumUses(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
        {
            return 0;
        }

        if (l <= tl && r >= tr)
        {
            return t[v];
        }

        int mid = (tl + tr) / 2;
        return GetSumUses(2 * v + 1, tl, mid, l, Math.Min(r, mid)) +
               GetSumUses(2 * v + 2, mid + 1, tr, Math.Max(l, mid + 1), r);
    }

    public int GetMax(int l, int r)
    {
        return GetMaxUses(0, 0, size - 1, l, r);
    }

    private int GetMaxUses(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
        {
            return 0;
        }

        if (l == tl && r == tr)
        {
            return t[v];
        }

        int mid = (tl + tr) / 2;
        return Math.Max(GetMaxUses(2 * v + 1, tl, mid, l, Math.Min(r, mid)),
                        GetMaxUses(2 * v + 2, mid + 1, tr, Math.Max(l, mid + 1), r));
    }

    public int GetMin(int l, int r)
    {
        return GetMinUses(t, 0, 0, size - 1, l, r);
    }

    private int GetMinUses(int[] t, int v, int tl, int tr, int l, int r)
    {
        if (l > r)
        {
            return int.MaxValue;
        }

        if (l == tl && r == tr)
        {
            return t[v];
        }

        else {
            int mid = (tl + tr) / 2;
            return Math.Min(GetMinUses(t, 2 * v + 1, tl, mid, l, Math.Min(r, mid)),
                            GetMinUses(t, 2 * v + 2, mid + 1, tr, Math.Max(l, mid + 1), r));
        }
        
    }

    public void Update(int pos, int val)
    {
        UpdateUses(0, 0, size - 1, pos, val);
    }

    private void UpdateUses(int v, int tl, int tr, int pos, int new_val)
    {
        if (tl == tr)
        {
            t[v] = new_val;
        }
        else
        {
            int mid = (tl + tr) / 2;
            if (pos <= mid)
                UpdateUses(2 * v + 1, tl, mid, pos, new_val);
            else
                UpdateUses(2 * v + 2, mid + 1, tr, pos, new_val);

            t[v] = t[v * 2 + 1] + t[v * 2 + 2];
        }
    }



    static void Main(string[] args)
    {
        int[] input = { 1, 3, 5, 7, 9, 11 };
        SegmentTree st = new SegmentTree(input);

        // Example queries
        Console.WriteLine(st.GetSum(1, 3));  // Output: 15 (sum of elements 3, 5, 7)
        Console.WriteLine(st.GetMin(2, 4));  // Output: 21 (sum of elements 5, 7, 9)
        Console.WriteLine(st.GetMax(1, 3));
        st.Update(1, 8);
        Console.WriteLine(st.GetSum(1, 3));
        Console.WriteLine(st.GetMin(1, 3));
        Console.WriteLine(st.GetMax(1, 3));
        Console.ReadLine();
    }
}
