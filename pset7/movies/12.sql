SELECT title FROM movies
WHERE id IN
(SELECT A.movie_id
FROM stars A, stars B
WHERE A.person_id = (SELECT id FROM people WHERE name = "Johnny Depp")
AND B.person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter")
AND A.movie_id = B.movie_id);