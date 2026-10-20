bool checkSpecial(int i, int n)
{
    if (n < 5)
        return false;
    if (i < 100000)
    {
        int dig1 = i % 10;
        i /= 10;
        int dig2 = i % 10;
        i /= 10;
        int dig3 = i % 10;
        i /= 10;
        if (i == dig1 * 10 + dig2 && dig3 + 2 * dig2 + 2 * dig1 == n)
            return true;
    }
    else
    {
        if (n % 2 == 1)
            return false;
        int dig1 = i % 10;
        i /= 10;
        int dig2 = i % 10;
        i /= 10;
        int dig3 = i % 10;
        i /= 10;
        if (i == dig1 * 100 + dig2 * 10 + dig3 && 2 * dig3 + 2 * dig2 + 2 * dig1 == n)
            return true;
    }
    return false;
}