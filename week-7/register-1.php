<?php

if (empty($_POST['name']) || empty($_POST['gender']) || empty($_POST['dorm'])) {
    header('Location: froshims-1.php');
    exit;
}

?>

<!DOCTYPE html>
<html>
    <head>
        <title>Frosh IMs</title>
    </head>    
    <body>
        <pre>
            <?php print_r($_POST); ?>
        </pre>
    </body>
</html>