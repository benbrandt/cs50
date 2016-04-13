<!DOCTYPE html>
<html>
    <head>
        <title>Frosh IMs</title>
    </head>
    <body style="text-align: center;">
        <h1>Register for Frosh IMs</h1>
        <form action="register-0.php" method="post">
            Name: <input name="name" type="text">
            <br>
            <input name="captain" type="checkbox"> Captain?
            <br>
            <input name="gender" type="radio" value="F"> Female
            <input name="gender" type="radio" value="M"> Male
            <br>
            Dorm:
            <select name="dorm">
                <option value=""></option>
                <option value="Apley Court">Apley Court</option>
                <option value="Canaday">Canaday</option>
                <option value="Grays">Grays</option>
            </select>
            <br>
            <input type="submit" value="Register">
        </form>
    </body>
</html>