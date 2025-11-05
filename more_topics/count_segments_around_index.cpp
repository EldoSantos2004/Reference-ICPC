// count of segments that include i with at most size k, at most l to the left and at most r to the right

auto calc = [&](ll val, ll mxx, ll left, ll right) -> ll{
    left = min(left, mxx - 1);
    right = min(right, mxx - 1);
    ll mn = min(left, right);
    ll mx = max(left, right);
    mn++;
    ll res = (mn * (mn + 1)) / 2;
    mn--;
    ll dif = mx - mn;
    res += dif * (mn + 1);
    mxx = min(mxx, left + right + 1);
    ll dif1 = mxx - mx - 1;
    res += (mn * (mn + 1)) / 2;
    dif1 = mn - dif1;
    res -= (dif1 * (dif1 + 1)) / 2;
    return res;
  };
