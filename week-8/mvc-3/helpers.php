<?php

/**
 * Renders template.
 */
function render($template, $data = [])
{
    $path = $template . ".php";
    if (file_exists($path))
    {
        extract($data);
        require($path);
    }
}
