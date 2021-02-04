when(102, 10).
when(108, 12).
when(341, 14).
when(455, 16).
when(452, 17).
where(102, z23).
where(108, z11).
where(341, z06).
where(455, 207).
where(452, 207).
enroll(a, 102).
enroll(a, 108).
enroll(b, 102).
enroll(c, 108).
enroll(d, 341).
enroll(e, 455).

schedule(S, P, T):-
	enroll(S, X),
	where(X, P),
	when(X, T).

usage(P, T):-
	where(X, P),
	when(X, T).

conflict(X, Y):-
	where(X, X1),
	where(Y, Y1),
	X \== Y,
	X1 == Y1,
	where(X, X2),
	where(Y, Y2),
	X \==Y,
	X2 == Y2.

meet(X, Y):-
	schedule(X, A, B),
	schedule(Y, K, L),
	X \== Y,
	A == B,
	K == L.  