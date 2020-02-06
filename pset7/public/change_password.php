<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        // if username blank, apologize
        
        if (empty($_POST["currentpassword"]))
        {
            apologize("You must provide your current password.");
        }
        
        // query database for user
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        
        // first (and only) row
        $row = $rows[0];
        
         // compare hash of user's input against hash that's in database
        if (!(crypt($_POST["currentpassword"], $row["hash"]) == $row["hash"]))
        {
            apologize("Current password does not match.");
        }
        // check if password blank
        else if (empty($_POST["newpassword"]))
        {
            apologize("You must provide your new password.");
        }
        // check if confirmation password blank
        else if (empty($_POST["confirmnewpassword"]))
        {
            apologize("You must confirm your password.");
        }
        // make sure password and confirmation password match, else apologize
        else if ($_POST["newpassword"] != $_POST["confirmnewpassword"])
        {
            apologize("Passwords do not match.");
        }
        
        // add user to database
       // query("INSERT INTO users(hash) VALUES(?)", crypt($_POST["newpassword"]));
        query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["newpassword"]), $_SESSION["id"]); 
       //query("UPDATE users SET cash = cash + $transaction WHERE id = ?",$_SESSION["id"]);      
       

        // redirect to portfolio
        redirect("/history.php");
        
                
        // else apologize
        apologize("Invalid username and/or password.");
        
    }
    else
    {
        // else render form
        render("change_password_form.php", ["title" => "Register"]);
    }

?>
