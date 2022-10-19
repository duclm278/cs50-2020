SELECT name FROM people
WHERE id IN
(SELECT A.person_id
FROM stars A, stars B
WHERE B.person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)
AND A.person_id != B.person_id
AND A.movie_id = B.movie_id
GROUP BY A.person_id);