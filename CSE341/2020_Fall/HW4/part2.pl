:- style_check(-singleton).

flight(istanbul, antalya).
flight(istanbul, izmir).
flight(istanbul, gaziantep).
flight(istanbul, ankara).
flight(istanbul, van).
flight(istanbul, rize).
flight(rize, van).
flight(ankara, van).
flight(ankara, konya).
flight(konya, antalya).
flight(gaziantep, antalya).
flight(burdur, isparta).
flight(isparta, izmir).
flight(erzincan, edremit).
flight(edremit, edirne).

distance(istanbul, antalya, 483).
distance(istanbul, izmir, 329).
distance(istanbul, gaziantep, 848).
distance(istanbul, ankara, 352).
distance(istanbul, van, 1263).
distance(istanbul, rize, 968).
distance(rize, van, 373).
distance(ankara, van, 921).
distance(ankara, konya, 228).
distance(konya, antalya, 193).
distance(gaziantep, antalya, 593).
distance(burdur, isparta, 25).
distance(isparta, izmir, 309).
distance(erzincan, edremit, 736).
distance(edremit, edirne, 915).

min([M],M).

min([X,Y|Z],M) :-
    X =< Y, min([X|Z],M).

min([X,Y|Z],M) :-
    X > Y,  min([Y|Z],M).

direct_route(X, Y, D):- distance(X, Y, D).
direct_route(X, Y, D):- distance(Y, X, D).

sroute(X,Y,Shortest) :-
   findall(D, find_route(X,Y,A,D), Ds), min(Ds, Shortest).

find_route(X, Y, A, D):- 
    search_route(X, Y, [X], A, D).

search_route(X, Y, P, [Y|P], D):- 
    direct_route(X,Y,D).

search_route(X, Y, Routed, A, D):-
    direct_route(X, Z, D1), not(Z == Y), not(is_member(Z, Routed)),           
    search_route(Z, Y, [Z|Routed],A,D2), D is D1+D2.

is_member(Item, [Item|Rest]).

is_member(Item, [X|Rest]):-
	is_member(Item, Rest).