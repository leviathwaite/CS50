<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        // if username blank, apologize
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        // check if password blank
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        // check if confirmation password blank
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        // make sure password and confirmation password match, else apologize
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match.");
        }
        
        // query database for user
        $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // if we found user, apologize
        if (count($rows) == 1)
        {
            apologize("That username appears to be taken.");
        }
        
        // add user to database
        query("INSERT INTO users(username, hash, cash) 
            VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
                
        // get users id
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
                
        // remember that user's now logged in by storing user's ID in session
        $_SESSION["id"] = $id;

        // redirect to portfolio
        redirect("/index.php");
        
                
        // else apologize
        apologize("Invalid username and/or password.");
        
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
