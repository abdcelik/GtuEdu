:- style_check(-singleton).

element(E, S):-
	is_member(E, S).

union(S1, S2, S3):-
	perform_union(S1, S2, C),
	equivalent(S3, C).

intersect(S1, S2, S3):-
	perform_intersect(S1, S2, C),
	equivalent(S3, C).

equivalent(S1, S2):-
	subset(S1, S2),
	subset(S2, S1).

is_member(Item, [Item|Rest]).
is_member(Item, [Ignore|Rest]):-
	is_member(Item, Rest).

perform_union([], X, X).
perform_union([Item|RestA], ItemB, [Item|RestC]):-	
	perform_union(RestA, ItemB, RestC).

perform_intersect([], X, []).
perform_intersect([Item|RestA], ItemB, [Item|RestC]):-
	element(Item, ItemB),
	perform_intersect(RestA, ItemB, RestC).

perform_intersect([Ignore|Rest], B, C):-
	perform_intersect(Rest, B, C).

subset([], X).
subset([Item|Rest], ItemB):-		
	element(Item, ItemB),
	subset(Rest, ItemB).