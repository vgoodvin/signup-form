/**
 * @file script.js
 *
 * Scripts for the SignUp form.
 */

$(document).ready(function () {
  /**
   * Validates email address.
   *
   * @param email
   * @return {Boolean}
   */
  var isEmailValid = function (email) {
    var emailPattern = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return emailPattern.test(email);
  };

  /**
   * Makes highlight effect for an element on the page.
   */
  $.fn.highlight = function() {
    $(this).fadeTo('slow', 0.5).fadeTo('slow', 1.0).fadeTo('slow', 0.5).fadeTo('slow', 1.0);
  };

  /**
   * Validates form values on page before submitting.
   */
  $('#signup-form').bind('submit', function () {
    var errors = [];
    if (!isEmailValid($('#edit-email').val())) {
      errors.push('Please enter valid email address');
    }
    if ($('#edit-pass').val().length < 6) {
      errors.push('Please enter at least 6 symbols in the password field');
    }
    if (errors.length) {
      // Add error messages to the page if any.
      var $messages = $('ul#messages').html('');
      $.each(errors, function (i, error) {
        $messages.append('<li>' + error + '</li>');
      });
      $messages.highlight();
      // Stop form submission.
      return false;
    }
  });
});
