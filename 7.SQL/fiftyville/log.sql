-- Keep a log of any SQL queries you execute as you solve the mystery.
-- crime_scene_reports
SELECT id,description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- interviews
SELECT transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
-- bakery_security_logs -- people name
SELECT p.name, p.phone_number
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
WHERE b.year = 2023
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND b.minute >= 15
    AND b.minute <= 25
    AND b.activity = 'exit';
-- atm_transactions  atm. Leggett Street  who withdraw
SELECT  transaction_type,account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type='withdraw';
--  bank_accounts
SELECT p.name, p.phone_number,atm.account_number
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
JOIN bank_accounts ba ON ba.person_id =p.id
JOIN atm_transactions atm ON atm.account_number =ba.account_number
WHERE b.year = 2023
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND b.minute >= 15
    AND b.minute <= 25
    AND b.activity = 'exit'
    AND atm.year=2023
    AND atm.month=7
    AND atm.day=28
    AND atm.atm_location = 'Leggett Street'
    AND atm.transaction_type='withdraw';
SELECT p.name, p.phone_number,ba.account_number
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
JOIN bank_accounts ba ON ba.person_id =p.id
JOIN atm_transactions atm ON atm.account_number =ba.account_number
WHERE b.year = 2023
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND b.minute >= 15
    AND b.minute <= 25
    AND b.activity = 'exit'
    AND atm.atm_location = 'Leggett Street'
    AND atm.transaction_type='withdraw';
-- phone_calls
-- --------+----------------+----------------+
-- | name  |  phone_number  | account_number |
-- +-------+----------------+----------------+
-- | Bruce | (367) 555-5533 | 49610011       |
-- | Diana | (770) 555-1861 | 26013199       |
-- | Iman  | (829) 555-5269 | 25506511       |
-- | Luca  | (389) 555-5198 | 28500762       |

SELECT caller,receiver,duration FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;


SELECT p.name, p.phone_number,ba.account_number,caller,receiver,fs.origin_airport_id,fs.destination_airport_id,ps.passport_number
FROM bakery_security_logs b
JOIN people p ON b.license_plate = p.license_plate
JOIN bank_accounts ba ON ba.person_id =p.id
JOIN atm_transactions atm ON atm.account_number =ba.account_number
JOIN phone_calls pc ON pc.caller = p.phone_number
JOIN flights fs ON fs.passport_number = p.passport_number
JOIN passengers ps ON fs.id =ps.flight_id
WHERE b.year = 2023
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND b.minute >= 15
    AND b.minute <= 25
    AND b.activity = 'exit'
    AND atm.year =2023
    AND atm.month = 7
    AND atm.day =28
    AND atm.atm_location = 'Leggett Street'
    AND atm.transaction_type='withdraw'
    AND pc.year = 2023
    AND pc.month = 7
    AND pc.day = 28
    AND pc.duration < 60;
    AND fs.year =2023
    AND fs.month =7
    And fs.day = 29
-- flights Bruce Diana
+-------+----------------+----------------+----------------+----------------+
| name  |  phone_number  | account_number |     caller     |    receiver    |
+-------+----------------+----------------+----------------+----------------+
| Bruce | (367) 555-5533 | 49610011       | (367) 555-5533 | (375) 555-8161 |
| Diana | (770) 555-1861 | 26013199       | (770) 555-1861 | (725) 555-3243 |
+-------+----------------+----------------+----------------+----------------+
SELECT fs.id,fs.origin_airport_id,fs.destination_airport_id,pa.passport_number FROM flights fs JOIN passengers pa ON fs.id =pa.flight_id JOIN people p ON p.passport_number =pa.passport_number  WHERE year = 2023 AND month = 7 AND day = 29;


JOIN phone_calls pc ON pc.caller = p1.phone_number
JOIN people p2 ON p2.phone_number =pc.receiver
JOIN passengers ps ON p2.passport_number =ps.passport_number
JOIN flights fs  ON fs.id =ps.flight_id


SELECT p1.name,p1.phone_number,p1.passport_number,ps.flight_id,pc.receiver,p2.name,p2.passport_number,air.city
FROM bakery_security_logs b
JOIN people p1 ON b.license_plate = p1.license_plate
JOIN bank_accounts ba ON ba.person_id =p1.id
JOIN atm_transactions atm ON atm.account_number =ba.account_number
JOIN passengers ps ON p1.passport_number = ps.passport_number
JOIN flights fs ON fs.id =ps.flight_id
JOIN phone_calls pc ON pc.caller = p1.phone_number
JOIN people p2 On p2.phone_number =pc.receiver
JOIN airports air ON air.id = fs.destination_airport_id
WHERE b.year = 2023
  AND b.month = 7
  AND b.day = 28
  AND b.hour = 10
  AND b.minute >= 15
  AND b.minute <= 25
  AND b.activity = 'exit'
  AND atm.year =2023
  AND atm.month = 7
  AND atm.day =28
  AND atm.atm_location = 'Leggett Street'
  AND atm.transaction_type='withdraw'
  AND fs.year =2023
  AND fs.month =7
  AND fs.day = 29
  AND pc.year = 2023
  AND pc.month = 7
  AND pc.day = 28
  AND pc.duration < 60
  ORDER BY fs.id LIMIT 1;


SELECT p1.name,p1.passport_number,p2.name,fs.id,fs.year, fs.month, fs.day, fs.hour, fs.minute,air.city
FROM bakery_security_logs b
JOIN people p1 ON b.license_plate = p1.license_plate
JOIN bank_accounts bs ON bs.person_id =p1.id
JOIN atm_transactions atm ON atm.account_number =bs.account_number
JOIN phone_calls ps ON ps.caller = p1.phone_number
JOIN people p2 ON p2.phone_number=ps.receiver
JOIN passengers pg ON pg.passport_number =p1.passport_number
JOIN flights fs ON fs.id = pg.flight_id
JOIN airports air ON air.id =fs.destination_airport_id
WHERE b.year = 2023
  AND b.month = 7
  AND b.day = 28
  AND b.hour = 10
  AND b.minute >= 15
  AND b.minute <= 25
  AND atm.year =2023
  AND atm.month = 7
  AND atm.day =28
  AND atm.atm_location = 'Leggett Street'
  AND atm.transaction_type='withdraw'
  AND ps.year = 2023
  AND ps.month = 7
  AND ps.day = 28
  AND duration < 60
  AND fs.year =2023
  AND fs.month =7
  AND fs.day = 29
  ORDER BY fs.year, fs.month, fs.day, fs.hour, fs.minute LIMIT 1 ;

