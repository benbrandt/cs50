<?php

require("PHPMailer/class.phpmailer.php");

if (!empty($_POST['name']) && !empty($_POST['gender']) && !empty($_POST['dorm'])) {
    $mail = new PHPMailer();
    
    $mail->IsSMTP();
    $mail->Host = "smtp.fas.harvard.edu";
    
    $mail->SetFrom("jharvard@cs50.net");
    
    $mail->AddAddress("jharvard@cs50.net");

    $mail->Subject = "registration";
    
    $mail->Body =
        "This person just registered:\n\n" .
        "Name: " . $_POST['name'] . "\n" .
        "Captain: " . $_POST['captain'] . "\n" .
        "Gender: " . $_POST['gender'] . "\n" .
        "Dorm: " . $_POST['dorm'];
        
    if ($mail->Send() == false) {
        die($mail->ErrInfo);
    }
}

?>

<!DOCTYPE html>
<html>
    <head>
        <title>Frosh IMs</title>
    </head>    
    <body>
        <?php if (empty($_POST['name']) || empty($_POST['gender']) || empty($_POST['dorm'])): ?>
            You must provide your name, gender, and dorm! Go <a href="froshims-2.php">back</a>.
        <?php else: ?>
            You are registered! (Well, not really.)
        <?php endif; ?>
    </body>
</html>