using System;
using System.Collections.Generic;

class Point
{
    public int x;
    public int y;

    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}

class ConvexHull
{
    static int CrossProduct(Point O, Point A, Point B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    static List<Point> ConvexHullGrahamScan(List<Point> P)
    {
        int n = P.Count, k = 0;
        Point[] H = new Point[2 * n];

        P.Sort((a, b) =>
        {
            if (a.x == b.x)
                return a.y - b.y;
            return a.x - b.x;
        });

        for (int i = 0; i < n; ++i)
        {
            while (k >= 2 && CrossProduct(H[k - 2], H[k - 1], P[i]) <= 0)
                k--;
            H[k++] = P[i];
        }

        for (int i = n - 2, t = k + 1; i >= 0; i--)
        {
            while (k >= t && CrossProduct(H[k - 2], H[k - 1], P[i]) <= 0)
                k--;
            H[k++] = P[i];
        }

        Array.Resize(ref H, k - 1);
        return new List<Point>(H);
    }

    static double CalculatePerimeter(List<Point> polygon)
    {
        double perimeter = 0;
        for (int i = 0; i < polygon.Count - 1; i++)
        {
            perimeter += Math.Sqrt(Math.Pow(polygon[i + 1].x - polygon[i].x, 2) + Math.Pow(polygon[i + 1].y - polygon[i].y, 2));
        }
        perimeter += Math.Sqrt(Math.Pow(polygon[0].x - polygon[polygon.Count - 1].x, 2) + Math.Pow(polygon[0].y - polygon[polygon.Count - 1].y, 2));
        return perimeter;
    }

    static void Main(string[] args)
    {
        Console.WriteLine("Введите количество точек:");
        int n = int.Parse(Console.ReadLine());
        List<Point> points = new List<Point>();

        for (int i = 0; i < n; i++)
        {
            Console.WriteLine($"Введите координаты {i + 1}-й точки (x y):");
            string[] input = Console.ReadLine().Split(' ');
            int x = int.Parse(input[0]);
            int y = int.Parse(input[1]);
            points.Add(new Point(x, y));
        }

        List<Point> convexHull = ConvexHullGrahamScan(points);
        double perimeter = CalculatePerimeter(convexHull);
        Console.WriteLine($"Периметр минимального охватывающего многоугольника: {perimeter:f2}");
        Console.ReadKey();
    }
}
