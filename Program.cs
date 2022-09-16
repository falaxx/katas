using System;
using System.Collections;

public class Program
{
    struct ThreeStrings
    {
        public string   stringA;  
        public string   stringB;
        public string   stringC;  
    }

    static void findThreeStringsWithSameHashcode(ref ThreeStrings ret, int i = 0)
    {
        var firstOccurence      = new Dictionary<int, int>();
        var secondOccurence     = new Dictionary<int, int>();
        string currentString    = i.ToString();
        while (true)
        {
            currentString = i.ToString();
            try
            {
                firstOccurence.Add(currentString.GetHashCode(),i);
            }
            catch (ArgumentException)
            {
                try
                {
                    secondOccurence.Add(currentString.GetHashCode(),i);
                }
                catch (ArgumentException)
                {
                    ret.stringA = firstOccurence[currentString.GetHashCode()].ToString();
                    ret.stringB = secondOccurence[currentString.GetHashCode()].ToString();
                    ret.stringC = currentString;
                    return;
                }
            }
            i++;
        }
    }

    static bool IsStringsDifferentHashsEqual(ThreeStrings strings)
    {
        return  !strings.stringA.Equals(strings.stringB) && !strings.stringB.Equals(strings.stringC)
                && !strings.stringA.Equals(strings.stringC) && strings.stringA.GetHashCode() == strings.stringB.GetHashCode() 
                && strings.stringB.GetHashCode() == strings.stringC.GetHashCode();
    }

    static void Main(string[] args)
    {
        var avg             = 0.0;
        var worst           = 0.0;
        var best            = 0.0;
        int count           = 0;
        Random randomNumber = new Random();
        int randomInt       = 0;
        ThreeStrings ret    = new ThreeStrings();
        while(true)
        {
            randomInt = randomNumber.Next();
            var watch = System.Diagnostics.Stopwatch.StartNew();

            findThreeStringsWithSameHashcode(ref ret,randomInt);
            watch.Stop();
            Console.WriteLine("Found: '{0}', '{1}', '{2}' in {3} ms",
                ret.stringA, ret.stringB, ret.stringC, watch.ElapsedMilliseconds);
            Console.WriteLine("HashCodes: '{0}', '{1}', '{2}', HashCodes equal? {3} ",
                ret.stringA.GetHashCode(), ret.stringB.GetHashCode(), ret.stringC.GetHashCode(),IsStringsDifferentHashsEqual(ret));
            avg = (avg*count + watch.ElapsedMilliseconds ) / (count+1) ;
            if (watch.ElapsedMilliseconds > worst)
                worst = watch.ElapsedMilliseconds;
            if (watch.ElapsedMilliseconds < best || best == 0.0)
                best = watch.ElapsedMilliseconds;
            Console.WriteLine("Average time for computing: {0} ms, best: {1} ms, worst: {2} ms, {3} iterations", avg, best, worst, count + 1);
            count++;
        }
    }
}
