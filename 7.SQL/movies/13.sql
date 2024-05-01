SELECT distinct p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN stars s_kb ON s.movie_id = s_kb.movie_id
JOIN people p_kb ON p_kb.id = s_kb.person_id
WHERE p_kb.name ='Kevin Bacon' AND p_kb.birth=1958 AND p.id!=p_kb.id;
