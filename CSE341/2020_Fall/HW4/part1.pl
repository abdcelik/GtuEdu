% knowledge base.
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

% rules
direct_route(X, Y):-
    flight(X, Y).

direct_route(X, Y):-
    flight(Y, X).

route(X, Y):-
    search_route(X, Y, []).

search_route(X, Y, List):-
    direct_route(X, Z),
    not(member(Z, List)),
    (Y = Z; search_route(Z, Y, [X | List])).