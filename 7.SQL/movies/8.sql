SELECT name FROM stars JOIN people ON people.id = stars.person_id JOIN movies on stars.movie_id = movies.id WHERE title LIKE 'Toy Story%';
