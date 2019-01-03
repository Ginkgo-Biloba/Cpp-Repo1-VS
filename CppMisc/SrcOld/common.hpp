#pragma once

template<bool Cond, class Tp1, class Tp2>
struct If_ {};

template<class Tp1, class Tp2>
struct If_<true, Tp1, Tp2> { typedef Tp1 type; };

template<class Tp1, class Tp2>
struct If_<false, Tp1, Tp2> { typedef Tp2 type; };

