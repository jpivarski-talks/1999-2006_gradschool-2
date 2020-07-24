;;; user variables

(defvar eucalyptus-ssh-username "mccann" "Username for ssh tunnel")
(defvar eucalyptus-ssh-password nil "Password for ssh tunnel")
(defvar eucalyptus-ssh-hostname "fledge.watson.org" "Hostname for ssh tunnel")
(defvar eucalyptus-ssh-program "ssh" "Local ssh command")
(defvar eucalyptus-ssh-program-switches nil "Extra switches for the local ssh command")
(defvar eucalyptus-ssh-program-command nil "Remote command to be executed via ssh")
(defvar eucalyptus-seed-randomizer t "Nil for predictable local port numbers, t to seed random number generator.")
(defvar eucalyptus-ssh-password-prompt "password: " "Regexp for password prompt.")
(defvar eucalyptus-ssh-welcome-message "welcome" "Regexp for noticing that you've been logged in.")
(defvar eucalyptus-ssh-farewell-message "Connection to .* closed."
  "Regexp for noticing that you've been logged out.")
(defvar eucalyptus-imap-hostname "cyrus.watson.org" "Hostname for remote imap machine")
(defvar eucalyptus-imap-port 143 "Port for remote imap machine")
(defvar eucalyptus-imap-username "mccann" "Username for imap machine")
(defvar eucalyptus-imap-password nil "Password for imap machine")
(defvar eucalyptus-imap-password-is-ssh-password t
  "nil if you need to be prompted for your imap password after you
have already given your ssh password")
(defvar eucalyptus-imap-welcome-message "server ready" "Regexp for noticing that you've been logged in.")

(defvar eucalyptus-default-mailbox "INBOX")

(defvar eucalyptus-control-header nil "Control buffer header")
(if (null eucalyptus-control-header)
    (setq eucalyptus-control-header
	  (format "
		      EUCALYPTUS CONTROL BUFFER

"
		  )))

(defvar eucalyptus-control-footer nil "Control buffer footer")
(if (null eucalyptus-control-footer)
    (setq eucalyptus-control-footer
	  (format "
key             binding
---             -------
 v              change connection variables
 i              establish simple imap connection
                     as %s on %s port %d
 t              establish secure imap connection
                     as %s on %s port %d
                     through ssh tunnel on %s@%s

 r              revive selected ssh tunnel
 c              check for new mail on selected imap
 l              list mailboxes on selected imap
 g              go to mailbox on selected imap

RET             enter selected buffer
 n              next buffer
 p              prev buffer
 d              delete buffer and kill associated processes
M-l             refresh this buffer list
 q              quit
"
		  eucalyptus-imap-username
		  eucalyptus-imap-hostname
		  eucalyptus-imap-port
		  eucalyptus-imap-username
		  eucalyptus-imap-hostname
		  eucalyptus-imap-port
		  eucalyptus-ssh-username
		  eucalyptus-ssh-hostname
		  )))

(defvar eucalyptus-tmp-directory "~/tmp" "A directory to create and
delete files in.")
(defvar eucalyptus-lynx "lynx" "A program which can be used to format
HTML with the -dump option.")

;;; eucalyptus control mode

(defvar eucalyptus-tree nil
  "Starting point for the eucalyptus data structure.")

(defvar eucalyptus-has-randomized nil
  "t if eucalyptus has already called for a random seed.")

(defvar eucalyptus-control-buffer nil "Points to the eucalyptus control buffer.")

(defvar eucalyptus-control-buffers-begin nil "To know where the buffer
lines begin and end.")
(defvar eucalyptus-control-buffers-end nil "To know where the buffer
lines begin and end.")

(defvar eucalyptus-control-mode-map () "Keymap used in eucalyptus control buffer")
(if (null eucalyptus-control-mode-map)
    (progn
      (setq eucalyptus-control-mode-map (make-sparse-keymap))
      (define-key eucalyptus-control-mode-map "v" 'eucalyptus-change-variables)
      (define-key eucalyptus-control-mode-map "i" 'eucalyptus-imap-connect)
      (define-key eucalyptus-control-mode-map "t" 'eucalyptus-ssh-tunnel)
      (define-key eucalyptus-control-mode-map "r" 'eucalyptus-ssh-revive)
      (define-key eucalyptus-control-mode-map "c" 'eucalyptus-check-new-mail)
      (define-key eucalyptus-control-mode-map "l" 'eucalyptus-list-mailboxes)
      (define-key eucalyptus-control-mode-map "g" 'eucalyptus-goto-mailbox)
  
      (define-key eucalyptus-control-mode-map "RET" 'eucalyptus-control-switch-to-buffer)
      (define-key eucalyptus-control-mode-map "\C-j" 'eucalyptus-control-switch-to-buffer)
      (define-key eucalyptus-control-mode-map "\C-m" 'eucalyptus-control-switch-to-buffer)
      (define-key eucalyptus-control-mode-map "n" 'eucalyptus-control-next-buffer)
      (define-key eucalyptus-control-mode-map "p" 'eucalyptus-control-prev-buffer)
      (define-key eucalyptus-control-mode-map "d" 'eucalyptus-control-delete-buffer)
      (define-key eucalyptus-control-mode-map "\M-l" 'eucalyptus)
      (define-key eucalyptus-control-mode-map "q" 'eucalyptus-control-quit)
      ))

(defun eucalyptus-control-mode ()
  "Major mode for navigating eucalyptus buffers.
Commands:
\\{eucalyptus-control-mode-map}"
  (interactive)
  (kill-all-local-variables)
  (use-local-map eucalyptus-control-mode-map)
  (setq major-mode 'eucalyptus-control-mode)
  (setq mode-name "Eucalyptus Control")
  )

;;; eucalyptus control functions

(defun eucalyptus ()
  "Create and/or bring the eucalyptus control buffer to front."
  (interactive)

  (let ((buf (get-buffer-create "*eucalyptus control*"))
	(i 0) (pointline) (pointcol))
    (setq eucalyptus-control-buffer buf)
    (switch-to-buffer buf)
    (setq pointline (count-lines 1 (min (1+ (point)) (point-max))))
    (setq pointcol (current-column))
    (setq buffer-read-only nil)
    (erase-buffer)
    (insert eucalyptus-control-header)

    (setq eucalyptus-control-buffers-begin (1+ (point)))

    (eucalyptus-verify-tree)
    (while (< i (length eucalyptus-tree))
      (eucalyptus-control-insert-node (nth i eucalyptus-tree) 0)
      (setq i (1+ i))
      ) ; end while

    (setq eucalyptus-control-buffers-end (1- (point)))

    (insert eucalyptus-control-footer)
    (goto-line pointline)
    (move-to-column pointcol)

    ) ; end let buf, i
  (setq buffer-read-only t)
  (eucalyptus-control-mode)
  )

(defun eucalyptus-control-insert-node (node depth)
  "Write just one node."

  (let ((status-char " "))
    (cond ((string-equal "SSH" (plist-get node 'type))
	   (if (and (plist-get node 'connected)
		    (string-equal (process-status (get-process (plist-get node 'process)))
				  "run"))
	       (setq status-char "*"))
	   ) ; end cond case

	  ((string-equal "IMAP" (plist-get node 'type))
	   (if (and (plist-get node 'connected)
		    (string-equal (process-status (get-process (plist-get node 'process)))
				  "open"))
	       (setq status-char "*"))
	   ) ; end cond case
	  ) ; end cond
	   
    (insert (format "%s %s%s\n"
		    status-char
		    (make-string (* 4 depth) ? )
		    (buffer-name (plist-get node 'buffer))
		    ) ; end format
	    ) ; end insert
    ) ; end let

  (let ((i 0))
    (while (< i (length (plist-get node 'children)))
      (eucalyptus-control-insert-node (nth i (plist-get node 'children)) (1+ depth))
      (setq i (1+ i))
      ) ; end while
    ) ; end let
      
  )

(defun eucalyptus-verify-tree ()
  "Walks through the tree and scans for killed buffers."

  (let ((i 0))
    (while (< i (length eucalyptus-tree))
      (eucalyptus-verify-node (nth i eucalyptus-tree))
      (setq i (1+ i))
      ) ; end while
    ) ; end let

  )

(defun eucalyptus-verify-node (node)
  "Walks through a node and scans for killed buffers."

  ;; a killed buffer has nil for a buffer-name
  (if (null (buffer-name (plist-get node 'buffer)))
      (let ((path (eucalyptus-find-path (plist-get node 'buffer) eucalyptus-tree))
	    (parent) (child))
	
	(cond ((= (length path) 1)
	       (setq parent nil)
	       (setq child (nth 0 path)))
	      
	      (t
	       (setq parent (nth (- (length path) 2) path))
	       (setq child (nth (1- (length path)) path)))
	      ) ; end cond
	(eucalyptus-delete-child parent child)

	t  ; true for "yes, we did kill somebody"
	) ; end let

    (let ((i 0))
      (while (< i (length (plist-get node 'children)))
	(if (not (eucalyptus-verify-node (nth i (plist-get node 'children))))
	    (setq i (1+ i))
	  ) ; end if
	) ; end while
      ) ; end let

    nil  ; false for "no, nobody has been killed"
    ) ; end if
  )

(defun eucalyptus-find-node (buffer root)
  "Find a node given its buffer and a root to start with."

  (let ((i 0) (found nil))
    (while (and (null found)
		(< i (length root)))

      (if (eq buffer (plist-get (nth i root) 'buffer))
	  (setq found (nth i root))
	(setq found (eucalyptus-find-node buffer (plist-get (nth i root) 'children)))
	) ; end if

      (setq i (1+ i))
      ) ; end while
    found
    ) ; end let
  )

(defun eucalyptus-find-path (buffer root)
  "Find a path to a node given its buffer and a root to start with."

  (let ((i 0) (found nil))
    (while (and (null found)
		(< i (length root)))

      (if (eq buffer (plist-get (nth i root) 'buffer))
	  (setq found (list (nth i root)))

	;; else
	(setq found (eucalyptus-find-path buffer (plist-get (nth i root) 'children)))
	(if found (setq found (cons (nth i root) found)))

	) ; end if

      (setq i (1+ i))
      ) ; end while
    found
    ) ; end let
  )

(defun eucalyptus-add-child (parent-buffer child)
  "Add a child leaf to a parent given the parent's buffer (returns
child if successful, nil otherwise). Adds a new trunk if
parent-buffer is nil."

  (if (null parent-buffer)
      (setq eucalyptus-tree (cons child eucalyptus-tree))

    ;; else
    (let ((parent (eucalyptus-find-node parent-buffer eucalyptus-tree)))
      (if parent
	  (plist-put parent 'children (cons child (plist-get parent 'children)))
	nil
	) ; end if parent-buffer found
      ) ; end let

    ) ; end if parent-buffer is nil

  child
  )

(defun eucalyptus-delete-child (parent child)
  "Delete a child and everything recursively below it. Supply nil for
parent if the child is a trunk."
  
  ;; first run this function on all of the child's children
  (let ((i 0))
    (while (< i (length (plist-get child 'children)))
      (eucalyptus-delete-child child (nth i (plist-get child 'children)))
      ) ; end while
    ) ; end let

  (cond ((string-equal (plist-get child 'type) "IMAP")
	 (if (and (plist-get child 'connected)
		  (string-equal (process-status (get-process (plist-get child 'process)))
				"open"))
	     ;; Be sure you don't give this a response function which
	     ;; tries to select the (possibly killed) buffer.
	     (eucalyptus-imap-send-command-internal child
						    "logout"
						    'eucalyptus-imap-null-response
						    nil)
	   ) ; end if
	 (delete-process (plist-get child 'process))
	 ) ; end if this is an imap node

	((string-equal (plist-get child 'type) "SSH")
	 (let ((oldbuf (current-buffer)))
	   (if (buffer-name (plist-get child 'buffer))
	       (progn
		 (set-buffer (plist-get child 'buffer))
		 (if (and (plist-get child 'connected)
			  (string-equal (process-status (get-process (plist-get child 'process)))
					"run"))
		     (progn
		       (insert "exit") (comint-send-input)
		       ) ) ; end progn end if
		 (set-buffer oldbuf)
		 ) ; end progn
	     ) ; end if buffer exists
	   ) ; end let
	 (delete-process (plist-get child 'process))
	 ) ; end if this is an ssh node

	) ; end cond

  (if (buffer-name (plist-get child 'buffer))
      (kill-buffer (plist-get child 'buffer)))

  (if (null parent)
      (if (equal child (car eucalyptus-tree))
	  ;; if it is first in the list, cut out the car by reassignment
	  (setq eucalyptus-tree (cdr eucalyptus-tree))
	;; if it is not first, it can be removed without reassignment
	;; (delete is a destructive function when the element is not first)
	(delete child eucalyptus-tree)
	) ; end if child is first in the list

    (plist-put parent 'children (delete child (plist-get parent 'children)))
    ) ; end if null parent
  )

(defun eucalyptus-control-selected-buffer ()
  "Get a buffer from under the cursor."

  (if (and (>= (1+ (point)) eucalyptus-control-buffers-begin)
	   (< (1- (point)) eucalyptus-control-buffers-end))
      (progn
	(save-excursion
	  (let (begin end bufname)
	    (beginning-of-line)
	    (forward-char 2) ; because of the status-char
	    (skip-chars-forward " \t")
	    (setq begin (point))
	    (end-of-line)
	    (skip-chars-backward " \t")
	    (setq end (point))
	    (setq bufname (buffer-substring begin end))
	    
	    (if (not (null (get-buffer bufname)))

		(get-buffer bufname) ; return the buffer

	      (message (format "There is no buffer named \"%s\"." bufname))
	      (unwind-protect (eucalyptus))
	      nil ; return nil

	      ) ; end if

	    ) ) ; end let end save-excursion

	)
    nil ; return nil if no buffers are selected
    ) ; end progn end if
  )

(defun eucalyptus-control-switch-to-buffer ()
  "Switch to the buffer named under the cursor."
  (interactive)

  (let ((buffer (eucalyptus-control-selected-buffer)))
    (if buffer
	(switch-to-buffer buffer)
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-control-next-buffer (&optional arg)
  "Step to the next buffer."
  (interactive "p")

  (if (> (- eucalyptus-control-buffers-end eucalyptus-control-buffers-begin) -2)

      (if (and (>= (1+ (point)) eucalyptus-control-buffers-begin)
	       (< (1- (point)) eucalyptus-control-buffers-end))
	  (progn

	    (if (null arg) (setq arg 1))

	    (while (> arg 0)
	      (end-of-line)
	      (if (< (point) eucalyptus-control-buffers-end)
		  (forward-char 1))
	      (setq arg (1- arg))
	      ) ; end while
	
	    (beginning-of-line)
	    (forward-char 2) ; because of the status-char
	    (skip-chars-forward " \t")

	    ) ; end progn

	(if (< (1+ (point)) eucalyptus-control-buffers-begin)
	    (progn

	      (goto-char eucalyptus-control-buffers-begin)
	      (beginning-of-line)
	      (forward-char 2) ; because of the status-char
	      (skip-chars-forward " \t")
	      
	      )) ; end progn end if
	
	) ; end if-else within block

    ) ; end if block size is more than two
  )

(defun eucalyptus-control-prev-buffer (&optional arg)
  "Step to the next buffer."
  (interactive "p")

  (if (> (- eucalyptus-control-buffers-end eucalyptus-control-buffers-begin) -2)

      (if (and (>= (1+ (point)) eucalyptus-control-buffers-begin)
	       (< (1- (point)) eucalyptus-control-buffers-end))
	  (progn
  
	    (if (null arg) (setq arg 1))
	
	    (while (> arg 0)
	      (beginning-of-line)
	      (if (>= (point) eucalyptus-control-buffers-begin)
		  (backward-char 1))
	      (setq arg (1- arg))
	      ) ; end while
	
	    (beginning-of-line)
	    (forward-char 2) ; because of the status-char
	    (skip-chars-forward " \t")
	
	    ) ; end progn

	(if (>= (1- (point)) eucalyptus-control-buffers-end)
	    (progn

	      (goto-char eucalyptus-control-buffers-end)
	      (beginning-of-line)
	      (forward-char 2) ; because of the status-char
	      (skip-chars-forward " \t")

	      )) ; end progn end if after block

	) ; end if-else within block
    ) ; end if block size is more than two
  )

(defun eucalyptus-control-delete-buffer ()
  "Delete the buffer named under the cursor and kill all the processes
attached. If there are dependancies, kill them as well."
  (interactive)

  (let ((buffer (eucalyptus-control-selected-buffer)))
    (if buffer
	(let ((path (eucalyptus-find-path buffer eucalyptus-tree))
	      (parent) (child))

	  (if (null path)
	      (error (format "There is no buffer named \"%s\" in the tree."
			     (buffer-name buffer)))
	    )
	  (cond ((= (length path) 1)
		 (setq parent nil)
		 (setq child (nth 0 path)))

		((>= (length path) 2)
		 (setq parent (nth (- (length path) 2) path))
		 (setq child (nth (1- (length path)) path)))
		) ; end cond

	  (eucalyptus-delete-child parent child)

	  (unwind-protect (eucalyptus))
	  ) ; end let path parent child
      ) ; end if buffer
    ) ; end let buffer
  )

(defun eucalyptus-control-quit ()
  "Delete all buffers and kill the control buffer"
  (interactive)

  (if (y-or-n-p "Kill all connections and buffers? ")
      (let ((i 0))
	(while (< i (length eucalyptus-tree))
	  (eucalyptus-delete-child nil (nth i eucalyptus-tree))
	  ) ; end while
	(kill-buffer (get-buffer "*eucalyptus control*"))
	(message "The horror... the horror...")
	) ; end let
    ) ; end if
  )

;;; the ssh tunnel functions

(defun eucalyptus-ssh-tunnel ()
  "Start up an ssh tunnel and then run an imap connection through it."
  (interactive)

  (let (password imap-password)
    (if (null eucalyptus-ssh-password)
	(setq password (read-passwd (format "SSH password for %s@%s: "
					    eucalyptus-ssh-username
					    eucalyptus-ssh-hostname)))
      (setq password eucalyptus-ssh-password)
      ) ; end if

    (if (null eucalyptus-imap-password)
	(if eucalyptus-imap-password-is-ssh-password
	    (setq imap-password password)
	  (setq imap-password (read-passwd (format "IMAP password for %s@%s: "
						   eucalyptus-imap-username
						   eucalyptus-imap-hostname))))
      (setq imap-password eucalyptus-imap-password)
      ) ; end if

    (if (and eucalyptus-seed-randomizer
	     (not eucalyptus-has-randomized))
	(random t)
      ) ; end if

    (eucalyptus-ssh-tunnel-internal eucalyptus-ssh-username
				    password
				    eucalyptus-ssh-hostname
				    eucalyptus-imap-hostname
				    eucalyptus-imap-port
				    (+ 1025 (random (- 65536 1025)))
				    eucalyptus-ssh-program
				    eucalyptus-ssh-program-switches
				    eucalyptus-ssh-program-command
				    eucalyptus-imap-username
				    imap-password
				    )
    ) ; end let
  )

(defun eucalyptus-ssh-tunnel-internal
  (username password hostname remote-machine remote-port local-port
	    ssh-program switches command imap-username imap-password)
  "What actually does all the work in the ssh tunnel establishment."

  (let (node)

    ;; the ardurous task of opening a (possibly) second shell
    (let ((another-shell (not (null (get-buffer "*shell*"))))
	  (other-shell-buffer)
	  (my-shell-buffer))
      (if another-shell
	  (progn
	    (shell)
	    (setq other-shell-buffer (current-buffer))
	    (rename-buffer "*shell-TEMPORARILY RENAMED*")
	    )) ; end progn end if
      (shell)
      (setq my-shell-buffer (current-buffer))
      (rename-buffer (format "SSH: %s@%s %s:%d --> local port %d"
			     username hostname remote-machine remote-port local-port)
		     t)
      (if another-shell
	  (progn
	    (set-buffer other-shell-buffer)
	    (rename-buffer "*shell*")
	    (set-buffer my-shell-buffer)
	    )) ; end progn end if
      ) ; end let

    (setq node (list 'children nil
		     'buffer (current-buffer)
		     'type "SSH"
		     'process (get-buffer-process (current-buffer))
		     'username username
		     'password password
		     'hostname hostname
		     'remote-machine remote-machine
		     'remote-port remote-port
		     'local-port local-port
		     'tried-password nil
		     'connected nil
		     'ssh-program ssh-program
		     'switches switches
		     'command command
		     'imap-username imap-username
		     'imap-password imap-password
		     ))
    (eucalyptus-add-child nil node)
    
    ;; set up two filters to catch password-prompt and connection events
    (if (not (memq 'eucalyptus-ssh-catch-password comint-output-filter-functions))
	(setq comint-output-filter-functions
	      (cons 'eucalyptus-ssh-catch-password comint-output-filter-functions)
	      ) ; end setq
      ) ; end if
    (if (not (memq 'eucalyptus-ssh-notice-welcome comint-output-filter-functions))
	(setq comint-output-filter-functions
	      (cons 'eucalyptus-ssh-notice-welcome comint-output-filter-functions)
	      ) ; end setq
      ) ; end if
    (if (not (memq 'eucalyptus-ssh-notice-farewell comint-output-filter-functions))
	(setq comint-output-filter-functions
	      (cons 'eucalyptus-ssh-notice-farewell comint-output-filter-functions)
	      ) ; end setq
      ) ; end if
    
    ;; now send the command through the shell!
    (if (null switches) (setq switches ""))
    (if (null command) (setq command ""))
    (insert (format "%s -L %d:%s:%d %s -l %s %s %s"
		    ssh-program local-port remote-machine remote-port
		    switches username hostname command))
    (comint-send-input)
    (message (format "Connecting to %s..." hostname))

    ) ; end outer let
  )

(defun eucalyptus-ssh-revive ()
  "Reconnects an ssh tunnel in a given shell buffer."
  (interactive)

  (let ((buffer (eucalyptus-control-selected-buffer)))
    (if buffer
	(let ((node (eucalyptus-find-node buffer eucalyptus-tree))
	      (switches) (command))
	  (if (not (string-equal (plist-get node 'type) "SSH"))
	      (error (format "The buffer \"%s\" is not an ssh tunnel" (buffer-name buffer))))

	  (if (null (plist-get node 'connected))
	      (progn
		(set-buffer buffer)

		(setq switches (plist-get node 'switches))
		(setq command (plist-get node 'command))
		(plist-put node 'tried-password nil)

		(if (null switches) (setq switches ""))
		(if (null command) (setq command ""))
		(insert (format "%s -L %d:%s:%d %s -l %s %s %s"
				(plist-get node 'ssh-program)
				(plist-get node 'local-port)
				(plist-get node 'remote-machine)
				(plist-get node 'remote-port)
				switches
				(plist-get node 'username)
				(plist-get node 'hostname)
				command))
		(comint-send-input)
		(message (format "Connecting to %s..."
				 (plist-get node 'hostname)))
		) ; end progn if not connected

	    (eucalyptus-imap-connect-internal (plist-get node 'imap-username)
					      (plist-get node 'imap-password)
					      "localhost"
					      (plist-get node 'local-port)
					      (plist-get node 'buffer))

	    (unwind-protect (eucalyptus))

	    ) ; end switch connected
	  ) ; end let node
      ) ; end if
    ) ; end let buffer
  )

(defun eucalyptus-ssh-catch-password (string)
  "Like `comint-watch-for-password-prompt' except that it communicates
the password to the rest of the eucalyptus suite."

  (if (string-match eucalyptus-ssh-password-prompt string)
      (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree)))

	(let ((username (plist-get node 'username))
	      (password (plist-get node 'password))
	      (hostname (plist-get node 'hostname))
	      )
	    
	  (if (plist-get node 'tried-password)
	      (setq password (read-passwd (format "Incorrect password. %s@%s's ssh password: "
						  username hostname)))
	    ) ; end if
	  (send-invisible password)

	  (plist-put node 'tried-password t)
	  (plist-put node 'password password)
	  
	  ) ; end let
	) ; end let
    ) ; end if this is the password prompt

  )

(defun eucalyptus-ssh-notice-welcome (string)
  "Watches for `eucalyptus-ssh-welcome-message' to ensure that a
connection has been established."

  (if (string-match eucalyptus-ssh-welcome-message string)
      (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree)))

	(plist-put node 'connected t)

	(message (format "Connecting to %s... done!" (plist-get node 'hostname)))

	(eucalyptus-imap-connect-internal (plist-get node 'imap-username)
					  (plist-get node 'imap-password)
					  "localhost"
					  (plist-get node 'local-port)
					  (plist-get node 'buffer))
	) ) ; end let end if
  )

(defun eucalyptus-ssh-notice-farewell (string)
  "Watches for `eucalyptus-ssh-farewell-message' to ensure that a
connection has been established."

  (if (string-match eucalyptus-ssh-farewell-message string)
      (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree)))

	(plist-put node 'connected nil)
	
	(message (format "Connection to %s closed." (plist-get node 'hostname)))
	) ) ; end let end if
  )

;;; the imap connection functions

(defvar eucalyptus-imap-history nil "History list for imap command prompts.")
(defvar eucalyptus-imap-mailbox-history nil "History list for imap mailbox prompts.")
(defvar eucalyptus-imap-complete-mailbox-names "INBOX"
  "If non-nil, each new imap connection will download all mailbox
names that start with `eucalyptus-imap-complete-mailbox-names' (if
it's a string) to use as a tab-completion list.")
(defvar eucalyptus-imap-mailbox-name-characters "A-Za-z0-9\\.\\_-"
  "The regexp for matching a mailbox name from a LIST response.")

(defun eucalyptus-imap-connect ()
  "Connect to an imap server with the user settings (`eucalyptus-imap-...')."
  (interactive)

  (let (password)
    (if (null eucalyptus-imap-password)
	(setq password (read-passwd (format "IMAP password for %s@%s: "
					    eucalyptus-imap-username
					    eucalyptus-imap-hostname)))
      (setq password eucalyptus-imap-password)
      ) ; end if
    (eucalyptus-imap-connect-internal eucalyptus-imap-username
				      password
				      eucalyptus-imap-hostname
				      eucalyptus-imap-port
				      nil)
    ) ; end let
  (if (eq (current-buffer) eucalyptus-control-buffer) (eucalyptus))
  )

(defun eucalyptus-imap-connect-internal (username password hostname port parent-buffer)
  "What actually does all the work in the imap establishment."

  (let (oldbuf buffer process node)
    (setq oldbuf (current-buffer))
    (setq buffer (generate-new-buffer (format "IMAP: %s@%s:%d"
					      username hostname port)))
    (set-buffer buffer)
    (setq buffer-read-only t)
    (eucalyptus-imap-log-mode)
    (set-buffer oldbuf)

    (setq process (open-network-stream (format "IMAP connection to %s@%s:%d"
 					       username hostname port)
				       buffer hostname port))
    (if (not (string-equal (process-status process) "open"))
 	(error (format "Cannot connect to %s@%s:%d" username hostname port))
      ) ; end if
    
    (set-process-filter process 'eucalyptus-imap-process-filter)

    (setq node (list 'children nil
		     'buffer buffer
		     'type "IMAP"
		     'process process
		     'username username
		     'password password
		     'hostname hostname
		     'port port
		     'connected nil
		     'completions nil
		     'next-command 1
		     'pending-commands nil
		     'current-mailbox nil
		     ))
    (eucalyptus-add-child parent-buffer node)

    (eucalyptus-imap-send-command-internal node
					   (format "login %s %s" username password)
					   'eucalyptus-imap-login-response nil)
    (if eucalyptus-imap-complete-mailbox-names
	(if (stringp eucalyptus-imap-complete-mailbox-names)
	    (eucalyptus-imap-send-command-internal
	     node (format "list \"*\" \"%s*\"" eucalyptus-imap-complete-mailbox-names)
	     'eucalyptus-imap-completion-response nil)
	  (eucalyptus-imap-send-command-internal
	     node "list \"*\" \"*\"" 'eucalyptus-imap-completion-response nil)
	  ) ; end if eucalyptus-imap-complete-mailbox-names is a string
      ) ; end if eucalyptus-imap-complete-mailbox-names is non-nil

    node
    )
  )

(defun eucalyptus-imap-send-command-from-child (node command response data &optional nested)
  "Calls `eucalyptus-imap-send-command-internal' from a child node."
  
  (let ((path (eucalyptus-find-path (plist-get node 'buffer) eucalyptus-tree)))
    (cond ((null path)
	   (error "e-imap-send-command-from-child: path is null"))

	  ((= (length path) 1)
	   (error "e-imap-send-command-from-child: path has length 1"))

	  (t (eucalyptus-imap-send-command-internal (nth (- (length path) 2) path)
						    command response data nested))
	  ) ; end cond
    ) ; end let
  )

(defun eucalyptus-imap-find-imap (node)
  "Searches up the tree and finds an imap node that ancestors this node."

  (let (imap-node path)
    (if (string-equal (plist-get node 'type) "IMAP")
	(setq imap-node node)
      (setq path (eucalyptus-find-path (plist-get node 'buffer) eucalyptus-tree))
      (while (and (not imap-node) path)
	(if (string-equal (plist-get (car path) 'type) "IMAP")
	    (setq imap-node (car path))
	  (setq path (cdr path))
	  ) ; end if
	) ; end while
      (if (not imap-node)
	  (let (oldbuf (current-buffer))
	    (set-buffer (get-buffer "*scratch*"))
	    (goto-char (point-max))
	    (insert (prin1-to-string path))
	    (set-buffer oldbuf)
	    (error "e-imap-send-command-internal: no imap buffer in path (printed to *scratch*)")
	    ) ; end let
	) ; end if still no imap buffer
      ) ; end if didn't start with an imap buffer
    imap-node
    ) ; end let
  )

(defun eucalyptus-imap-send-command-internal (node command response data &optional nested swallowoutput)
  "Sends a command to an imap process and inserts a response function into the queue."

  (let ((imap-node (eucalyptus-imap-find-imap node)))

    (let ((process (plist-get imap-node 'process)))

      ;; we must check for a disconnected imap
      (if (not (string-equal (process-status process) "open"))
	  (let ((buffer (plist-get imap-node 'buffer))
		(username (plist-get imap-node 'username))
		(password (plist-get imap-node 'password))
		(hostname (plist-get imap-node 'hostname))
		(port (plist-get imap-node 'port))
		(newprocess)
		(oldbuf (current-buffer)))
	    (plist-put imap-node 'current-mailbox nil)

	    (if nested (error (format "Cannot re-connect to %s@%s:%d" username hostname port)))

	    (if (string-match "^logout$" command)
		nil ; do nothing

	      (message (format "Re-opening connection to %s@%s:%d" username hostname port))
	      (setq newprocess (open-network-stream (format "IMAP connection to %s@%s:%d"
							    username hostname port)
						    buffer hostname port))
	      (plist-put imap-node 'process newprocess)
	      (plist-put imap-node 'pending-commands nil) ; cancel all pending commands
	      (if (not (string-equal (process-status newprocess) "open"))
		  (error (format "Cannot re-connect to %s@%s:%d" username hostname port))
		(setq process newprocess)
		) ; end if re-connect failed
	      (set-process-filter newprocess 'eucalyptus-imap-process-filter)
	      
	      (eucalyptus-imap-send-command-internal imap-node
						     (format "login %s %s" username password)
						     'eucalyptus-imap-login-response nil t)
	      ) ; end if command is logout

	    ) ; end let
	) ; end if connection is down
      
      ;; we have a good imap
      (process-send-string process (format "out%06d %s\n" (plist-get imap-node 'next-command) command))
      
      ;; protect passwords from prying eyes!
      (if (string-match "^login " command)
	  (setq command (format "login %s %s"
				(plist-get imap-node 'username)
				(make-string (length (plist-get imap-node 'password)) ?.)
				))) ; end format end setq end if
      
      (let ((newcommand (list 'id (plist-get imap-node 'next-command)
			      'node node
			      'command command
			      'response response
			      'data data
			      'swallow swallowoutput
			      )))
	(plist-put imap-node 'pending-commands (cons newcommand (plist-get imap-node 'pending-commands)))
	) ; end let newcommand
      
      (plist-put imap-node 'next-command (1+ (plist-get imap-node 'next-command)))
      ) ; end let process
    
    ) ; end let imap-node

  )

(defun eucalyptus-imap-find-command (commands number)
  "Picks out a command from a pending-command list by number. Nil if missing."

  (let ((i 0) (done nil))
    (while (and (not done)
		(< i (length commands)))
      (if (= (plist-get (nth i commands) 'id) number)
	  (setq done t)
	(setq i (1+ i))
	) ; end if
      ) ; end while
    (if done
	(nth i commands)
      nil
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-imap-process-filter (process output)
  "Picks up the result of a command sent to the process and runs the response function."

  (let ((oldbuf (current-buffer))
	(maybe-more-output t)
	(imap-node (eucalyptus-find-node (process-buffer process) eucalyptus-tree))
	(default-marker))
    (progn
      ;; always put new output at the end
      (set-buffer (process-buffer process))
      (goto-char (point-max))
      (setq default-marker (point))
      (setq buffer-read-only nil)
      (insert output)
      (setq buffer-read-only t)

      ;; but maybe this isn't all of it
      (while maybe-more-output
	(set-buffer (process-buffer process))
	(if (null (marker-position (process-mark process)))
	    (set-marker (process-mark process) default-marker))
	(goto-char (process-mark process))

	(if (re-search-forward "^out[0-9]+ " nil t)
	    (let (fullline)
	      (save-excursion
		(end-of-line)
		(setq fullline (not (= (point) (point-max))))
		) ; end save-excursion
	      (if fullline
		  (let (longstart longend numstart statusstart end long num status
				  pending-commands this-command
				  response data node)
		    
		    ;; first get the status message because we're here
		    (setq statusstart (point))
		    (end-of-line)
		    (setq end (point))
		    (setq status (buffer-substring statusstart end))

		    ;; now go back for the number
		    (re-search-backward "t[0-9]+ " nil t)
		    (forward-char 1)
		    (setq numstart (point))
		    (setq num (string-to-number (buffer-substring numstart statusstart)))
		    (backward-char 3)
		    (setq longend (point-marker))

		    ;; and now go back for the long output
		    (goto-char (process-mark process))
		    (skip-chars-forward "[\r\n]")
		    (setq longstart (point-marker))
		    (setq long (buffer-substring (marker-position longstart) (marker-position longend)))

		    ;; finally, set the new process mark
		    (set-marker (process-mark process) end)

		    ;; insert the input command as a way of keeping log
		    (setq pending-commands (plist-get imap-node 'pending-commands))
		    (setq this-command
			  (eucalyptus-imap-find-command pending-commands num))
		    (setq buffer-read-only nil)
		    (if this-command
			(insert (format " in%06d %s\n" num (plist-get this-command 'command)))
		      (insert (format " in%06d ???\n" num))
		      ) ; end if
		    (setq longstart (point-marker))
		    
		    (if this-command
			(progn
			  (setq response (plist-get this-command 'response))
			  (setq data (plist-get this-command 'data))
			  (setq node (plist-get this-command 'node))
			  (if (plist-get this-command 'swallow)
			      (let ((amark (point-marker)))
				(delete-region (marker-position longstart) (marker-position longend))
				(goto-char longstart)
				(insert "[Output redirected...]\n")
				(goto-char amark)
				) ; end progn
			    ) ; end if
			  (setq pending-commands
				(delete this-command pending-commands))
			  )		; end progn
		      )			; end if
		    (setq buffer-read-only t)
		    (plist-put imap-node 'pending-commands pending-commands)

		    ;; now do what you came to do
		    (if this-command
			(condition-case err
			    (funcall response status long data node oldbuf)
			  (error (message (format "Error in response function: %s"
						  (error-message-string err))))
			  )		; end condition-case
		      )			; end if

		    ) ; end let a bunch of variables
		(setq maybe-more-output nil)
		) ; end if fullline
	      ) ; end let fullline
	  (setq maybe-more-output nil) ; this is the case where
				       ; we're simply waiting for
				       ; more data
	  ) ; end if we see an "out" tag
	) ; end while looking for more output lines
      ) ; end progn
    (goto-char (point-max))
    (set-buffer oldbuf)
    ) ; end of let
  )

(defun eucalyptus-imap-null-response (status response data node originbuffer)
  "An empty response function."
  )

(defun eucalyptus-imap-diagnostic-response (status response data node originbuffer)
  "A response function for debugging."

  (let ((oldbuf (current-buffer)))
    (set-buffer (get-buffer "*scratch*"))
    (goto-char (point-max))
    (insert (format "status = >%s<\nresponse = >%s<\ndata = %s\nnode = %s\noriginbuffer = %s\n\n"
		  status
		  response
		  (prin1-to-string data)
		  (prin1-to-string node)
		  (prin1-to-string originbuffer)))
    (set-buffer oldbuf)
    ) ; end let
  )

(defun eucalyptus-imap-login-response (status response data node originbuffer)
  "The response function for logging in."

  (if (string-match "^\* OK " response)
      (setq response (substring response 5)))
  (if (> (length response) 0)
      (setq response (substring response 0 -1)))

  (cond ((string-match "^OK" status)
	 (progn
	   (plist-put node 'connected t)
	   (if (eq originbuffer eucalyptus-control-buffer) (eucalyptus))
	   (message (if (> (length response) 0)
			(format "%s; %s" response status)
		      status
		      ))
	   ) ; end progn
	 ) ; end cond case

	((string-equal "NO Login incorrect" status)
	 (let (password)
	   (setq password (read-passwd (format "Incorrect password. %s@%s's imap password: "
					       (plist-get node 'username) (plist-get node 'hostname))))
	   (plist-put node 'password password)
	   (eucalyptus-imap-send-command-internal node
						  (format "login %s %s" (plist-get node 'username) password)
						  'eucalyptus-imap-login-response nil)
	   ) ; end let
	 ) ; end cond case

	(t (error (format "Login to %s@%s failed: %s"
			  (plist-get node 'username) (plist-get node 'hostname) status))
	   ) ; end cond case
	) ; end cond
  )

(defun eucalyptus-imap-completion-response (status response data node originbuffer)
  "The response function for getting a list of tab-completion variables."

  (if (string-match "^OK" status)
      (let ((oldbuffer (current-buffer))
	    (tmpbuffer (generate-new-buffer "*completions-temp*"))
	    (new-list nil)
	    (mailbox-name)
	    )
	(set-buffer tmpbuffer)
	(insert response)
	(beginning-of-buffer)
	(while (re-search-forward
		(concat "\"?\\([" eucalyptus-imap-mailbox-name-characters "]+\\)\"?$") nil t)
	  (setq mailbox-name (string-make-unibyte
			      (buffer-substring (match-beginning 1) (match-end 1))))
	  (setq new-list (cons (list mailbox-name) new-list))
	  ) ; end while
	(plist-put node 'completions new-list)
	(set-buffer oldbuffer)
	(kill-buffer tmpbuffer)
	) ; end let
    (error "Failed to retrieve tab-completion list")
    ) ; end if
  )

(defun eucalyptus-imap-get-mailbox-name (prompt node &optional original)
  
  (let ((completions (plist-get node 'completions))
	(retval))
    (if (null original)
	(setq original eucalyptus-imap-complete-mailbox-names)
      ) ; end if
    (if eucalyptus-imap-complete-mailbox-names
	(let ((oldvalue completion-ignore-case))
	  (setq completion-ignore-case t)
	  (setq retval (completing-read prompt completions nil nil original))
	  (setq completion-ignore-case oldvalue)
	  ) ; end let
      (read-string prompt original 'eucalyptus-imap-mailbox-history)
      ) ; end if
    retval
    ) ; end let
  )

(defvar eucalyptus-imap-log-mode-map () "Keymap used in imap log buffer")
(if (null eucalyptus-imap-log-mode-map)
    (progn
      (setq eucalyptus-imap-log-mode-map (make-sparse-keymap))
      (define-key eucalyptus-imap-log-mode-map " " 'eucalyptus-imap-send-command)
      (define-key eucalyptus-imap-log-mode-map "e" 'eucalyptus)
      (define-key eucalyptus-imap-log-mode-map "q" 'eucalyptus-imap-kill-imap)
      ))

(defvar eucalyptus-imap-log-mode-syntax-table nil "Syntax table used in imap log buffer")
(if (not eucalyptus-imap-log-mode-syntax-table)
    (progn
      (setq eucalyptus-imap-log-mode-syntax-table (make-syntax-table))
      
      ;; white space
      (modify-syntax-entry ?  " " mathematica-mode-syntax-table)  
      (modify-syntax-entry ?\t " " mathematica-mode-syntax-table)
      (modify-syntax-entry ?\f " " mathematica-mode-syntax-table)
      (modify-syntax-entry ?\n " " mathematica-mode-syntax-table)
      (modify-syntax-entry ?\^m " " mathematica-mode-syntax-table)

      ;; parens
      (modify-syntax-entry ?( "()" mathematica-mode-syntax-table)
      (modify-syntax-entry ?) ")(" mathematica-mode-syntax-table)

      ;; for mailbox names
      (modify-syntax-entry ?- "w" mathematica-mode-syntax-table)
      (modify-syntax-entry ?_ "w" mathematica-mode-syntax-table)
      (modify-syntax-entry ?. "w" mathematica-mode-syntax-table)

      ;; quotes
      (modify-syntax-entry ?\" "\"" mathematica-mode-syntax-table)

      ;; create an abbrev table for mathematica mode
      (define-abbrev-table 'eucalyptus-imap-log-mode-abbrev-table ())

      ) ; end progn
  ) ; end if

(setq eucalyptus-imap-log-mode-font-lock-keywords
  '(
    ("^ \\(in\\)\\([0-9]+\\).*\\( capability\\>\\| noop\\>\\| logout\\>\\| authenticate\\>\\| login\\>\\| select\\>\\| examine\\>\\| create\\>\\| delete\\>\\| renamee\\>\\| subscribe\\>\\| unsubscribe\\>\\| list\\>\\| lsub\\>\\| status\\>\\| append\\>\\| check\\>\\| close\\>\\| expunge\\>\\| search\\>\\| fetch\\>\\| store\\>\\| copy\\>\\| uid\\>\\| flags\\>\\| exists\\>\\| recent\\>\\| x[A-Za-z0-9]*\\>\\)" (1 font-lock-type-face) (2 font-lock-constant-face) (3 font-lock-function-name-face))
    ("^ \\(in\\)\\([0-9]+\\) " (1 font-lock-type-face) (2 font-lock-constant-face))

    ("^\\(\\*\\).*\\( capability\\>\\| noop\\>\\| logout\\>\\| authenticate\\>\\| login\\>\\| select\\>\\| examine\\>\\| create\\>\\| delete\\>\\| renamee\\>\\| subscribe\\>\\| unsubscribe\\>\\| list\\>\\| lsub\\>\\| status\\>\\| append\\>\\| check\\>\\| close\\>\\| expunge\\>\\| search\\>\\| fetch\\>\\| store\\>\\| copy\\>\\| uid\\>\\| flags\\>\\| exists\\>\\| recent\\>\\| x[A-Za-z0-9]*\\>\\)" (1 font-lock-type-face) (2 font-lock-function-name-face))
    ("^\\* " . font-lock-type-face)

    ("^\\(out\\)\\([0-9]+\\) \\(no .*\\|bad .*\\)$" (1 font-lock-type-face) (2 font-lock-constant-face) (3 font-lock-warning-face))
    ("^\\(out\\)\\([0-9]+\\) \\(ok .*\\|preauth .*\\|bye .*\\)" (1 font-lock-type-face) (2 font-lock-constant-face) (3 font-lock-keyword-face))

    ("\\(\\\\Noinferiors\\|\\\\Noselect\\|\\\\Marked\\|\\\\Unmarked\\|\\\\Seen\\|\\\\Answered\\|\\\\Flagged\\|\\\\Deleted\\|\\\\Draft\\|\\\\Recent\\)" . font-lock-builtin-face)

    ("inbox[A-Za-z0-9\\.\\-\\_]*" . font-lock-variable-name-face)

    ("NIL" . font-lock-builtin-face)

    ("\\[Output redirected\\.\\.\\.\\]" . font-lock-warning-face)

   )
  )

(defun eucalyptus-imap-log-mode ()
  "Mode for the imap log buffer."
  (interactive)
  (kill-all-local-variables)
  (use-local-map eucalyptus-imap-log-mode-map)
  (setq major-mode 'eucalyptus-imap-log-mode)
  (setq mode-name "IMAP Log")

  (setq local-abbrev-table eucalyptus-imap-log-mode-abbrev-table)
  (set-syntax-table eucalyptus-imap-log-mode-syntax-table)

  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults '(eucalyptus-imap-log-mode-font-lock-keywords nil t))
  )

(defun eucalyptus-imap-send-command ()
  "Send a command to the imap connection interactively."
  (interactive)

  (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree))
	(command))
    (if node
	(progn
	  (setq command
		(read-string "IMAP command: " nil 'eucalyptus-imap-history))
	  (eucalyptus-imap-send-command-internal node command					 
						 'eucalyptus-imap-diagnostic-response nil)
	  ) ; end progn
      (error "There is no eucalyptus node associated with this buffer")
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-imap-kill-imap ()
  "Kill this imap connection and its associated eucalyptus-tree node."
  (interactive)

  (let ((path (eucalyptus-find-path (current-buffer) eucalyptus-tree))
	(parent) (child))
    (if (null path)
	(error (format "This buffer, \"%s\", is not in the tree." (buffer-name (current-buffer)))))
    (if (not (string-equal (plist-get (nth (1- (length path)) path) 'type) "IMAP"))
	(error (format "This buffer, \"%s\", is not an imap log." (buffer-name (current-buffer)))))

    (cond ((= (length path) 1)
	   (setq parent nil)
	   (setq child (nth 0 path)))

	  ((>= (length path) 2)
	   (setq parent (nth (- (length path) 2) path))
	   (setq child (nth (1- (length path)) path)))
	  ) ; end cond

    (eucalyptus-delete-child parent child)
    (unwind-protect (eucalyptus))

    ) ; end let
  )

;;; mailbox listing

(defvar eucalyptus-list-mailboxes-mode-map () "Keymap used in mailbox listing")
(if (null eucalyptus-list-mailboxes-mode-map)
    (progn
      (setq eucalyptus-list-mailboxes-mode-map (make-sparse-keymap))
      (define-key eucalyptus-list-mailboxes-mode-map "RET" 'eucalyptus-list-mailboxes-open)
      (define-key eucalyptus-list-mailboxes-mode-map "\C-j" 'eucalyptus-list-mailboxes-open)
      (define-key eucalyptus-list-mailboxes-mode-map "\C-m" 'eucalyptus-list-mailboxes-open)
      (define-key eucalyptus-list-mailboxes-mode-map " " 'eucalyptus-list-mailboxes-expand)
      (define-key eucalyptus-list-mailboxes-mode-map "\M- " 'eucalyptus-list-mailboxes-expand-all)
      (define-key eucalyptus-list-mailboxes-mode-map "\M-l" 'eucalyptus-list-mailboxes-rescan)
      (define-key eucalyptus-list-mailboxes-mode-map "p" 'eucalyptus-list-mailboxes-prev)
      (define-key eucalyptus-list-mailboxes-mode-map "n" 'eucalyptus-list-mailboxes-next)
      (define-key eucalyptus-list-mailboxes-mode-map "P" 'eucalyptus-list-mailboxes-prev-same)
      (define-key eucalyptus-list-mailboxes-mode-map "N" 'eucalyptus-list-mailboxes-next-same)
      (define-key eucalyptus-list-mailboxes-mode-map "u" 'eucalyptus-list-mailboxes-up-one)
      (define-key eucalyptus-list-mailboxes-mode-map "d" 'eucalyptus-list-mailboxes-down-one)
      (define-key eucalyptus-list-mailboxes-mode-map "g" 'eucalyptus-goto-mailbox)
      (define-key eucalyptus-list-mailboxes-mode-map "e" 'eucalyptus)
      (define-key eucalyptus-list-mailboxes-mode-map "q" 'eucalyptus-list-mailboxes-kill)
      ))

(defun eucalyptus-list-mailboxes-mode ()
  "Mode for the list mailboxes buffer."
  (interactive)
  (kill-all-local-variables)
  (use-local-map eucalyptus-list-mailboxes-mode-map)
  (setq major-mode 'eucalyptus-list-mailboxes-mode)
  (setq mode-name "Mailbox Listing")

  ;; inherit these from imap-log-mode
  (setq local-abbrev-table eucalyptus-imap-log-mode-abbrev-table)
  (set-syntax-table eucalyptus-imap-log-mode-syntax-table)
  )

(defun eucalyptus-list-mailboxes ()
  "List mailboxes on the selected imap."
  (interactive)

  (let ((buffer (eucalyptus-control-selected-buffer)))
    (if buffer
	(let ((node (eucalyptus-find-node buffer eucalyptus-tree)))
	  (if (string-equal (plist-get node 'type) "IMAP")
	      (let ((boxbuffer (generate-new-buffer (format "MAILBOXES: %s@%s:%d"
							    (plist-get node 'username)
							    (plist-get node 'hostname)
							    (plist-get node 'port))))
		    (boxnode))
		(setq boxnode (list 'children nil
				    'buffer boxbuffer
				    'type "MAILBOXES"
				    'boxes nil
				    'timestamp "                        "
				    ))
		(eucalyptus-add-child buffer boxnode)
		(eucalyptus-imap-send-command-internal boxnode
						       "list \"\" \"%%\""
						       'eucalyptus-list-mailboxes-response
						       nil)
		) ; end let
	    (error (format "The buffer \"%s\" is not an imap buffer"
			   (buffer-name buffer)))
	    ) ; end if imap
	  ) ; end let node
      ) ; end if buffer
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-response (status response data node originbuffer)
  "A response function for listing mailboxes."

  (if (string-match "^OK" status)
      (let ((tmpbuffer (generate-new-buffer "*mailboxes-temp*"))
	    (boxes (plist-get node 'boxes)))
	(set-buffer tmpbuffer)
	(insert (string-make-unibyte response))
	(goto-char (point-min))
	(while (re-search-forward "LIST[ \t]+(" nil t)
	  (let (eoln noinferiors noselect marked unmarked)
	    (save-excursion (end-of-line) (setq eoln (point)))
	    (while (re-search-forward "\\\\[A-Za-z]+" eoln t)
	      (cond ((string-equal (buffer-substring (match-beginning 0) (match-end 0)) "\\Noinferiors")
		     (setq noinferiors t))
		    ((string-equal (buffer-substring (match-beginning 0) (match-end 0)) "\\Noselect")
		     (setq noselect t))
		    ((string-equal (buffer-substring (match-beginning 0) (match-end 0)) "\\Marked")
		     (setq marked t))
		    ((string-equal (buffer-substring (match-beginning 0) (match-end 0)) "\\Unmarked")
		     (setq unmarked t))
		    (t (error (format "List mailboxes format: wierd flag, see %s"
				      (buffer-name tmpbuffer))))
		    ) ; end cond
	      ) ; end foreach flag

	    (if (re-search-forward
		 (concat "\"?\\([" eucalyptus-imap-mailbox-name-characters "]+\\)\"?$") nil t)
		(let (name parts box)
		  (setq name (buffer-substring (match-beginning 1) (match-end 1)))
		  (setq parts (split-string name "\\."))
		  (setq box (list 'children nil
				  'line nil
				  'fullname name
				  'name (nth (1- (length parts)) parts)
				  'noinferiors noinferiors
				  'noselect noselect
				  'marked marked
				  'unmarked unmarked
				  'messages nil
				  'recent nil
				  'unseen nil
				  ))
		  (setq boxes (eucalyptus-list-mailboxes-insert node boxes parts box))
		  (if (not noselect)
		      (eucalyptus-imap-send-command-internal
		       node
		       (format "status \"%s\" (recent unseen messages)" name)
		       'eucalyptus-list-mailboxes-status-response
		       (list 'fullname name)) ; RFC doesn't say that status returns mailbox name
		    ) ; end if
		  ) ; end let
	      (error (format "List mailboxes format: wierd mailbox name, see %s"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    ) ; end let
	  ) ; end foreach list item

	(plist-put node 'boxes boxes)
	(kill-buffer tmpbuffer)

	(let (pointline pointcol)
	  (set-buffer (plist-get node 'buffer))
	  (setq pointline (count-lines 1 (min (1+ (point)) (point-max))))
	  (setq pointcol (current-column))
	  (setq buffer-read-only nil)
	  (erase-buffer)
	  (eucalyptus-list-mailboxes-draw node boxes 1 t)
	  (setq buffer-read-only t)
	  (goto-line pointline)
	  (move-to-column pointcol)
	  (eucalyptus-list-mailboxes-mode)
	  ) ; end let
	
	(if (eq (get-buffer "*eucalyptus control*") originbuffer) (unwind-protect (eucalyptus)))
	) ; end let tmpbuffer boxes
    (error (format "List mailboxes failed: %s" status))
    ) ; end if
  )

(defun eucalyptus-list-mailboxes-status-response (status response data node originbuffer)
  "A response function for checking the number of existing and recent messages in a mailbox."

  (let ((fullname (plist-get data 'fullname)))
    (if (string-match "^OK" status)
	(let ((tmpbuffer (generate-new-buffer "*mailboxes-status-temp*"))
	      (messages) (recent) (unseen))
	  (set-buffer tmpbuffer)
	  (insert (string-make-unibyte response))

	  (goto-char (point-min))
	  (if (re-search-forward "messages \\([0-9]+\\)" nil t)
	      (setq messages (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	    (error (format "Examine format: No \"MESSAGES #\" string, see %s"
			   (buffer-name tmpbuffer)))	    
	    )

	  (goto-char (point-min))
	  (if (re-search-forward "recent \\([0-9]+\\)" nil t)
	      (setq recent (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	    (error (format "Examine format: No \"RECENT #\" string, see %s"
			   (buffer-name tmpbuffer)))	    
	    )

	  (goto-char (point-min))
	  (if (re-search-forward "unseen \\([0-9]+\\)" nil t)
	      (setq unseen (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	    (error (format "Examine format: No \"UNSEEN #\" string, see %s"
			   (buffer-name tmpbuffer)))	    
	    )

 	  (eucalyptus-list-mailboxes-alter node fullname 'messages messages)
 	  (eucalyptus-list-mailboxes-alter node fullname 'recent recent)
 	  (eucalyptus-list-mailboxes-alter node fullname 'unseen unseen)

	  (let ((boxes (plist-get node 'boxes)) (box) (start) (end) (oldbuf (current-buffer)))
	    (setq box (eucalyptus-list-mailboxes-get-box node fullname))

	    (set-buffer (plist-get node 'buffer))
	    (plist-put node 'pointline (count-lines 1 (min (1+ (point)) (point-max))))
	    (plist-put node 'pointcol (current-column))

 	    (setq buffer-read-only nil)
 	    (goto-line (plist-get box 'line))
 	    (beginning-of-line)
 	    (setq start (point))
 	    (end-of-line)
 	    (setq end (min (1+ (point)) (point-max)))
 	    (delete-region start end)
 	    (eucalyptus-list-mailboxes-draw-line node boxes (plist-get box 'line) box)
; 	    (goto-char start)
; 	    (insert (format "%d %d %d "
; 			    (plist-get box 'line)
; 			    start
; 			    end))

	    (if (plist-get data 'last) (eucalyptus-list-mailboxes-stamp-time node))

 	    (setq buffer-read-only t)

	    (goto-line (plist-get node 'pointline))
	    (move-to-column (plist-get node 'pointcol))

	    (set-buffer oldbuf)

	    ) ; end let

	  (kill-buffer tmpbuffer)
	  ) ; end progn
      (error (format "Status %s (recent unseen messages) failed: %s" fullname status))
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-stamp-time (node)
  "This just updates a time stamp in the corner so the user knows how
recently mailboxes have been checked."

  (let (start end time)
    (setq buffer-read-only nil)
    (beginning-of-buffer)
    (end-of-line)
    (setq start (point))
    (backward-char 24)
    (setq end (point))
    (delete-region start end)
    (setq time (current-time-string))
    (insert time)
    (plist-put node 'timestamp time)
    (setq buffer-read-only t)
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-insert (node boxes parts box)
  "A function for inserting a mailbox into the mailbox list."

  (let ((i 0))
    (while (and (< i (length boxes))
		(not (string-equal (plist-get (nth i boxes) 'name) (car parts))))
      (setq i (1+ i))
      ) ; end while
    (if (= i (length boxes))
	(if (= (length parts) 1)
	    (setq boxes (nconc boxes (list box)))
	  ;; the new box doesn't yet have a parent in the list
	  (let (boxparts i parentparts parentname fakeparent)
	    (setq boxparts (split-string (plist-get box 'fullname) "\\."))
	    (setq i 0)
	    (setq parentparts nil)
	    (setq parentname "")
	    (while (< i (1+ (- (length boxparts) (length parts))))
	      (setq parentparts (nconc parentparts (list (nth i boxparts))))
	      (setq parentname (concat parentname (nth i boxparts)))
	      (setq i (1+ i))
	      (if (< i (1+ (- (length boxparts) (length parts))))
		  (setq parentname (concat parentname "."))
		) ; end if
	      ) ; end while	    

	    (setq fakeparent (list 'children nil
				   'line nil
				   'fullname parentname
				   'name (nth (1- (length parentparts)) parentparts)
				   'noinferiors nil
				   'noselect t
				   'marked nil
				   'unmarked nil
				   'messages nil
				   'recent nil
				   'unseen nil))
	    (setq boxes (nconc boxes (list fakeparent)))
	    (plist-put (nth (1- (length boxes)) boxes) 'children
		       (eucalyptus-list-mailboxes-insert node nil (cdr parts) box))
	    ) ; end let
	  ) ; end if length parts == 1
      (if (= (length parts) 1)
	  (progn
	    (plist-put box 'children (plist-get (nth i boxes) 'children))
	    (setq boxes (delete (nth i boxes) boxes))
	    (setq boxes (nconc boxes (list box)))
	    ) ; end progn
	(plist-put (nth i boxes) 'children
		   (eucalyptus-list-mailboxes-insert node
						     (plist-get (nth i boxes) 'children)
						     (cdr parts)
						     box))
	     ) ; end if length parts == 1
      ) ; end if parent was not found
    boxes
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-alter (node boxname attribute newvalue)
  "A function for altering an existing mailbox in the mailbox list."

  (let ((newboxes (eucalyptus-list-mailboxes-alter-internal
		   node
		   (plist-get node 'boxes)
		   (split-string boxname "\\.")
		   attribute
		   newvalue)))
    (if newboxes
	(plist-put node 'boxes newboxes)
      ;; alteration may fail silently
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-alter-internal (node boxes parts attribute newvalue)
  "A function for altering an existing mailbox in the mailbox list (internal)."

  (let ((i 0))
    (while (and (< i (length boxes))
		(not (string-equal (plist-get (nth i boxes) 'name) (car parts))))
      (setq i (1+ i))
      ) ; end while
    (if (not (= i (length boxes)))
	(cond ((= (length parts) 1)
	       (plist-put (nth i boxes) attribute newvalue)
	       )
	      (t (plist-put (nth i boxes) 'children
			    (eucalyptus-list-mailboxes-alter-internal
			     node
			     (plist-get (nth i boxes) 'children)
			     (cdr parts)
			     attribute
			     newvalue))
		 )
	      ) ; end cond
      nil
      ) ; end if
    boxes
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-get-box (node boxname)
  "A function for altering an existing mailbox in the mailbox list."

  (eucalyptus-list-mailboxes-get-box-internal node
					      (plist-get node 'boxes)
					      (split-string boxname "\\."))
  )

(defun eucalyptus-list-mailboxes-get-box-internal (node boxes parts)
  "A function for getting an existing mailbox from the mailbox list (internal)."

  (let ((i 0) (box))
    (while (and (< i (length boxes))
		(not (string-equal (plist-get (nth i boxes) 'name) (car parts))))
      (setq i (1+ i))
      ) ; end while
    (if (not (= i (length boxes)))
	(cond ((= (length parts) 1)
	       (setq box (nth i boxes))
	       )
	      (t (setq box (eucalyptus-list-mailboxes-get-box-internal
			    node
			    (plist-get (nth i boxes) 'children)
			    (cdr parts)
			    )) ; end euc... end setq
		 )
	      ) ; end cond
      nil
      ) ; end if
    box
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-draw (node boxes line &optional header)
  "Draw a mailbox list, given the information in boxes."

  (if header
      (progn
	(insert " NEW     MAILBOX NAME (size)                  ")
	(insert (plist-get node 'timestamp))
	(insert "\n")
	(insert "======================================================================\n")
	(setq line (+ line 2))
	)
    )

  (let ((i 0))
    (while (< i (length boxes))
      (eucalyptus-list-mailboxes-draw-line node boxes line (nth i boxes))

      (setq line (1+ line))
      (if (plist-get (nth i boxes) 'children)
	  (setq line (eucalyptus-list-mailboxes-draw node (plist-get (nth i boxes) 'children) line)))
    
      (setq i (1+ i))
      ) ; end while
    ) ; end let

  line
  )

(defun eucalyptus-list-mailboxes-draw-line (node boxes line box)
  "Draw one line in a mailbox listing (corresponding to one mailbox)."

  (let ((messages (plist-get box 'messages))
	(recent (plist-get box 'recent))
	(unseen (plist-get box 'unseen))
	(arrow) (name) (mark))
    
    (setq messages (if messages (format "(%d)" messages) ""))
;    (setq recent (if (and recent (> recent 0)) (format "%4d" recent) "    "))
    (setq unseen (if (and unseen (> unseen 0)) (format "%4d" unseen) "    "))
    
    (setq arrow (cond ((plist-get box 'noinferiors) " ")
		      ((plist-get box 'children) "v")
		      (t ">")))
    
    ;;; A nice idea, but very ugly
    ;;
;     (if (string-equal (plist-get box 'fullname) (plist-get box 'name))
;  	(setq name (plist-get box 'fullname))
;       (setq name (make-string (- (length (plist-get box 'fullname))
; 				 (length (plist-get box 'name))
; 				 2)
; 			      ? )
; 	    ) ; end setq
;       (setq name (concat name "." (plist-get box 'name)))
;       )
    (setq name (make-string (* 2 (1- (length (split-string (plist-get box 'fullname) "\\."))))
			    ? ))
    (setq name (concat name (plist-get box 'fullname)))	

    (setq mark (if (plist-get box 'marked) "*" " "))
    
    (insert (format "%s   %s %s %s\n" unseen arrow name messages))

    (eucalyptus-list-mailboxes-alter node (plist-get box 'fullname) 'line line)
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-find-line (boxes line)
  "Returns a box for a given line number."
  
  (let ((i 0) (box))
    (while (and (< i (length boxes))
		(null box))
      (if (= (plist-get (nth i boxes) 'line) line)
	  (setq box (nth i boxes))
	(if (plist-get (nth i boxes) 'children)
	    (setq box (eucalyptus-list-mailboxes-find-line
		       (plist-get (nth i boxes) 'children) line))
	  ) ; end if there are children
	) ; end if-else this is the line
      (setq i (1+ i))
      ) ; end while
    box
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-expand-all ()
  "Recursively expand the listing for the currently selected mailbox."
  (interactive)
  (eucalyptus-list-mailboxes-expand t)
  )

(defun eucalyptus-list-mailboxes-expand (&optional all)
  "Expand the listing for the currently selected mailbox."
  (interactive)

  (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree))
	(box))
    (if (or (not node) (not (string-equal (plist-get node 'type) "MAILBOXES")))
	(error "This buffer is not a mailbox listing")
      ) ; end if

    (setq box
	  (eucalyptus-list-mailboxes-find-line
	   (plist-get node 'boxes)
	   (count-lines 1 (min (1+ (point)) (point-max))) ; the "1" is for narrowing
	   )) ; end setq

    (plist-put node 'pointline (count-lines 1 (min (1+ (point)) (point-max))))
    (plist-put node 'pointcol (current-column))
    (if (and (plist-get box 'children) (not all))
	(progn
	  (eucalyptus-list-mailboxes-alter node (plist-get box 'fullname) 'children nil)
	  (setq buffer-read-only nil)
	  (erase-buffer)
	  (eucalyptus-list-mailboxes-draw node (plist-get node 'boxes) 1 t)
	  (setq buffer-read-only t)
	  (goto-line (plist-get node 'pointline))
	  (move-to-column (plist-get node 'pointcol))
	  ) ; end progn
      (eucalyptus-imap-send-command-internal node
					     (if all
						 (format "list \"\" \"%s\.*\""
							 (plist-get box 'fullname))
					       (format "list \"\" \"%s\.%%\""
						       (plist-get box 'fullname))
					       ) ; end if
					     'eucalyptus-list-mailboxes-response
					     nil)
      ) ; end if already open

    ) ; end let
  )

(defun eucalyptus-list-mailboxes-kill ()
  "Kill this list mailboxes buffer."
  (interactive)

    (let ((path (eucalyptus-find-path (current-buffer) eucalyptus-tree))
	(parent) (child))
    (if (null path)
	(error (format "This buffer, \"%s\", is not in the tree." (buffer-name (current-buffer)))))
    (if (not (string-equal (plist-get (nth (1- (length path)) path) 'type) "MAILBOXES"))
	(error (format "This buffer, \"%s\", is not a mailbox listing." (buffer-name (current-buffer)))))

    (cond ((= (length path) 1)
	   (setq parent nil)
	   (setq child (nth 0 path)))

	  ((>= (length path) 2)
	   (setq parent (nth (- (length path) 2) path))
	   (setq child (nth (1- (length path)) path)))
	  ) ; end cond

    (eucalyptus-delete-child parent child)
    (unwind-protect (eucalyptus))

    ) ; end let
  )

(defun eucalyptus-list-mailboxes-rescan ()
  "Resend a status request to every mailbox in the viewed listing."
  (interactive)

  (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree)))
    (if (or (not node) (not (string-equal (plist-get node 'type) "MAILBOXES")))
	(error "This buffer is not a mailbox listing")
      ) ; end if

    (let ((boxes (plist-get node 'boxes))
	  (i 0))
      (while (< i (length boxes))
	(eucalyptus-list-mailboxes-rescan-internal node (nth i boxes)
						   (= i (1- (length boxes)))
						   ) ; end send internal command
	(setq i (1+ i))
	) ; end while
      ) ; end let boxes, imap-node, i
    ) ; end let node
  )

(defun eucalyptus-list-mailboxes-rescan-internal (node box last)
  "Internal function to resend a status request to a viewed mailbox and its children."

  (let ((start) (end) (oldbuf (current-buffer)))
    (setq buffer-read-only nil)
    (set-buffer (plist-get node 'buffer))
    (save-excursion
      (beginning-of-buffer)
      (end-of-line)
      (setq start (point))
      (backward-char 24)
      (setq end (point))
      (delete-region start end)
      (insert "...waiting for update...")
      (plist-put node 'timestamp "...waiting for update...")
      ) ; end save-excursion
    (setq buffer-read-only t)
    (set-buffer oldbuf)
    ) ; end let

  (if (not (plist-get box 'noselect))
      (eucalyptus-imap-send-command-internal
       node
       (format "status \"%s\" (recent unseen messages)" (plist-get box 'fullname))
       'eucalyptus-list-mailboxes-status-response
       (list 'fullname (plist-get box 'fullname) ; RFC doesn't say that status returns mailbox name
	     'last last))
    ) ; end if
  
  (if (plist-get box 'children)
      (let ((children (plist-get box 'children)) (i 0))
	(while (< i (length children))
	  (eucalyptus-list-mailboxes-rescan-internal node (nth i children)
						   (= i (1- (length boxes)))
						   ) ; end send internal command
	  (setq i (1+ i))
	  ) ; end while
	) ; end let
    ) ; end if
  )

(defun eucalyptus-list-mailboxes-box-indentation ()
  "Determine the box indent on this line."

  (let ((formatted t))
    (save-excursion
      (beginning-of-line)
      (condition-case err (forward-char 9) (error (setq formatted nil)))
      (if formatted
	  (progn (skip-chars-forward " \t")
		 (current-column))
	nil
	) ; end if
      ) ; end save-excursion
    ) ; end let
  )

(defun eucalyptus-list-mailboxes-prev ()
  "Step back one mailbox."
  (interactive)

  (if (> (count-lines 1 (min (1+ (point)) (point-max))) 3) ; ignore in header
      (progn
	(previous-line 1)
	(move-to-column (eucalyptus-list-mailboxes-box-indentation))
	) ; end progn
    (error "Beginning of mailbox list")
    ) ; end if
  )

(defun eucalyptus-list-mailboxes-next ()
  "Step forward one mailbox."
  (interactive)

  (if (< (count-lines 1 (min (1+ (point)) (point-max))) 3) ; if in header
      (progn 
	(goto-line 3)
	(move-to-column (eucalyptus-list-mailboxes-box-indentation))
	) ; end progn

    (if (not (= (point) (point-max)))
	(let ((oldpos (point)))
	  (next-line 1)
	  (if (= (point) (point-max))
	      (progn
		(goto-char oldpos)
		(error "End of mailbox list")
		) ; end progn
	    (move-to-column (eucalyptus-list-mailboxes-box-indentation))
	    ) ; end if
	  ) ; end let
      (error "End of mailbox list")
      ) ; end if
    
    ) ; end if we're in the header
  )

(defun eucalyptus-list-mailboxes-prev-same ()
  "Step back one mailbox at the same level."
  (interactive)

  (if (> (count-lines 1 (min (1+ (point)) (point-max))) 3) ; ignore in header
      (let ((this (eucalyptus-list-mailboxes-box-indentation)))
	(if this
	    (let (new-point)
	      (save-excursion
		(previous-line 1)
		(while (and (eucalyptus-list-mailboxes-box-indentation)
			    (< this (eucalyptus-list-mailboxes-box-indentation)))
		  (previous-line 1))
		(if (eucalyptus-list-mailboxes-box-indentation)
		    (move-to-column (eucalyptus-list-mailboxes-box-indentation))
		  ) ; end if 
		(if (= this (eucalyptus-list-mailboxes-box-indentation))
		    (setq new-point (point))
		  ) ; end if
		) ; end save-excursion
	      (if new-point
		  (goto-char new-point)
		(error "Beginning of block")
		) ; end if
	      ) ; end let
	  (error "This mailbox line is not formatted right")
	  ) ; end if
	) ; end let
    (error "Beginning of block")
    ) ; end if
  )

(defun eucalyptus-list-mailboxes-next-same ()
  "Step forward one mailbox at the same level."
  (interactive)

  (if (< (count-lines 1 (min (1+ (point)) (point-max))) 3) ; ignore in header
      (progn 
	(goto-line 3)
	(move-to-column (eucalyptus-list-mailboxes-box-indentation))
	) ; end progn

    (if (not (= (point) (point-max)))
	(let ((this (eucalyptus-list-mailboxes-box-indentation)))
	  (if this
	      (let (new-point)
		(save-excursion
		  (next-line 1)
		  (if (not (= (point) (point-max)))
		      (progn
			(while (and (eucalyptus-list-mailboxes-box-indentation)
				    (< this (eucalyptus-list-mailboxes-box-indentation)))
			  (next-line 1))
			(if (eucalyptus-list-mailboxes-box-indentation)
			    (move-to-column (eucalyptus-list-mailboxes-box-indentation))
			  ) ; end if
			(if (= this (eucalyptus-list-mailboxes-box-indentation))
			    (setq new-point (point))
			  ) ; end if
			) ; end progn
		    ) ; end if not last line
		  ) ; end save-excursion
		(if new-point
		    (goto-char new-point)
		  (error "End of block")
		  ) ; end if
		) ; end let
	    (error "This mailbox line is not formatted right")
	    ) ; end if
	  ) ; end let
      (error "End of block")
      ) ; end if

    ) ; end if we're in the header
  )

(defun eucalyptus-list-mailboxes-up-one ()
  "Step out of this mailbox group."
  (interactive)

  (if (= (point) (point-max))
      (progn
	(previous-line 1)
	(move-to-column (eucalyptus-list-mailboxes-box-indentation))
	) ; end progn

    (if (> (count-lines 1 (min (1+ (point)) (point-max))) 3) ; ignore in header
	(let ((this (eucalyptus-list-mailboxes-box-indentation)))
	  (if this
	      (let (new-point)
		(save-excursion
		  (previous-line 1)
		  (while (and (eucalyptus-list-mailboxes-box-indentation)
			      (<= this (eucalyptus-list-mailboxes-box-indentation)))
		    (condition-case err
			(previous-line 1)
		      (error (error "No parenting blocks"))
		      ) ; end condition-case
		    ) ; end while
		  (if (eucalyptus-list-mailboxes-box-indentation)
		      (progn
			(move-to-column (eucalyptus-list-mailboxes-box-indentation))
			(setq new-point (point))
			) ; end progn
		    ) ; end if
		  ) ; end save-excursion
		(if new-point
		    (goto-char new-point)
		  (error "No parenting blocks")
		  ) ; end if
		) ; end let
	    (error "This mailbox line is not formatted right")
	    ) ; end if
	  ) ; end let
      (error "No parenting blocks")
      ) ; end if we're in header

    ) ; end if last line
  )

(defun eucalyptus-list-mailboxes-down-one ()
  "Step into the first available mailbox group."
  (interactive)

  (if (< (count-lines 1 (min (1+ (point)) (point-max))) 3) ; skip header
      (progn 
	(goto-line 3)
	(move-to-column (eucalyptus-list-mailboxes-box-indentation))
	) ; end progn

    (if (= (point) (point-max))
	(error "No offspring blocks")

      (let ((this (eucalyptus-list-mailboxes-box-indentation)))
	(if this
	    (let (new-point)
	      (save-excursion
		(next-line 1)
		(while (and (eucalyptus-list-mailboxes-box-indentation)
			    (>= this (eucalyptus-list-mailboxes-box-indentation)))
		  (condition-case err
		      (next-line 1)
		    (error (error "No offspring blocks"))
		    ) ; end condition-case
		  ) ; end while
		(if (eucalyptus-list-mailboxes-box-indentation)
		    (progn
		      (move-to-column (eucalyptus-list-mailboxes-box-indentation))
		      (setq new-point (point))
		      ) ; end progn
		  ) ; end if
		) ; end save-excursion
	      (if new-point
		  (goto-char new-point)
		(error "No offspring blocks")
		) ; end if
	      ) ; end let
	  (error "This mailbox line is not formatted right")
	  ) ; end if
	) ; end let

      ) ; end if we're on the last line
    ) ; end if we're in header
  )

(defun eucalyptus-list-mailboxes-open (arg)
  "Get a messages listing for the selected mailbox. A numerical prefix
argument is the number of messages to display (most recent)."
  (interactive "P")

  (let ((node (eucalyptus-find-node (current-buffer) eucalyptus-tree)))
    (if (or (not node) (not (string-equal (plist-get node 'type) "MAILBOXES")))
	(error "This buffer is not a mailbox listing")
      ) ; end if

    (if (and (> (count-lines 1 (min (1+ (point)) (point-max))) 2) ; ignore header
	     (not (= (point) (point-max)))
	     ) ; end and
	(let (box)
	  (setq box
		(eucalyptus-list-mailboxes-find-line
		 (plist-get node 'boxes)
		 (count-lines 1 (min (1+ (point)) (point-max))) ; the "1" is for narrowing
		 )) ; end setq
	  (if (plist-get box 'noselect)
	      (message "Not a selectable mailbox")
	    (eucalyptus-mailbox-open (plist-get box 'fullname) (eucalyptus-imap-find-imap node) arg)
	    ) ; end if noselect
	  ) ; end let
      ) ; end if we're even looking at a mailbox line item
    ) ; end let
  )

;;; mailbox listings

(defvar eucalyptus-mailbox-mode-map () "Keymap used in mailbox listing")
(if (null eucalyptus-mailbox-mode-map)
    (progn
      (setq eucalyptus-mailbox-mode-map (make-sparse-keymap))
      (define-key eucalyptus-mailbox-mode-map "RET" 'eucalyptus-mailbox-read-message)
      (define-key eucalyptus-mailbox-mode-map "\C-j" 'eucalyptus-mailbox-read-message)
      (define-key eucalyptus-mailbox-mode-map "\C-m" 'eucalyptus-mailbox-read-message)
      (define-key eucalyptus-mailbox-mode-map " " 'scroll-up)
      (define-key eucalyptus-mailbox-mode-map "-" 'scroll-down)
      (define-key eucalyptus-mailbox-mode-map "d" 'scroll-up) ; lambda expression for one line
      (define-key eucalyptus-mailbox-mode-map "u" 'scroll-down) ; lambda expression for one line
      (define-key eucalyptus-mailbox-mode-map "p" 'previous-line)
      (define-key eucalyptus-mailbox-mode-map "n" 'next-line)
      (define-key eucalyptus-mailbox-mode-map "P" 'eucalyptus-mailbox-prev-new)
      (define-key eucalyptus-mailbox-mode-map "N" 'eucalyptus-mailbox-next-new)
      (define-key eucalyptus-mailbox-mode-map "g" 'eucalyptus-goto-mailbox)
      (define-key eucalyptus-mailbox-mode-map "t" 'eucalyptus-mailbox-toggle-email)
      (define-key eucalyptus-mailbox-mode-map ":" 'eucalyptus-mailbox-select)
      (define-key eucalyptus-mailbox-mode-map "x" 'eucalyptus-mailbox-expunge)
      (define-key eucalyptus-mailbox-mode-map "e" 'eucalyptus)
      (define-key eucalyptus-mailbox-mode-map "q" 'eucalyptus-mailbox-kill)
      ))

(defun eucalyptus-mailbox-mode ()
  "Mode for the list mailboxes buffer."
  (interactive)
  (kill-all-local-variables)
  (use-local-map eucalyptus-mailbox-mode-map)
  (setq major-mode 'eucalyptus-mailbox-mode)
  (setq mode-name "Message Summary")

  ;; inherit these from imap-log-mode
  (setq local-abbrev-table eucalyptus-imap-log-mode-abbrev-table)
  (set-syntax-table eucalyptus-imap-log-mode-syntax-table)
  )

(defun eucalyptus-goto-mailbox (arg)
  "Prompt for and open a mailbox in the selected imap. The numerical
prefix argument is the number of messages to display (most recent)."
  (interactive "P")

  (let (buffer imap-node)
    (if (eq (current-buffer) (get-buffer "*eucalyptus control*"))
	(setq buffer (eucalyptus-control-selected-buffer))
      (setq buffer (current-buffer))
      ) ; end if
    (if buffer
	(progn
	  (setq imap-node (eucalyptus-imap-find-imap
			   (eucalyptus-find-node buffer eucalyptus-tree)))

	  (eucalyptus-mailbox-open
	   (eucalyptus-imap-get-mailbox-name "Go to mailbox: " imap-node) imap-node arg)
	  ) ; end progn
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-mailbox-open (name node number)
  "Get a messages listing for this mailbox."

  (let ((buffer (generate-new-buffer (format "SUMMARY: %s (%s@%s:%d)"
					     name
					     (plist-get node 'username)
					     (plist-get node 'hostname)
					     (plist-get node 'port))))
	(summary-node))
    (switch-to-buffer buffer)
    (eucalyptus-mailbox-mode)
    (insert "\n\n		Reading message listing from server...\n\n")
    (beginning-of-buffer)
    (setq buffer-read-only t)
    (setq truncate-lines t)

    (setq summary-node (list 'children nil
			     'buffer buffer
			     'type "SUMMARY"
			     'name name
			     'messages nil
			     'justemails nil
			     'limit number
			     ))
    (eucalyptus-add-child (plist-get node 'buffer) summary-node)
    (eucalyptus-mailbox-refresh-internal summary-node)
    ) ; end let
  )

(defun eucalyptus-mailbox-refresh-internal (node &optional oneline)
  "Re-fetch a list of mesages from the imap server (internal)."

  (let ((current-mailbox (plist-get (eucalyptus-imap-find-imap node) 'current-mailbox)))
    (if (and current-mailbox
 	     (string-equal current-mailbox (plist-get node 'name))
	     (or (not (numberp (plist-get node 'limit))) (numberp oneline))
 	     (string-equal (process-status (plist-get (eucalyptus-imap-find-imap node) 'process)) "open")
 	     ) ; end and
 	nil ; no need to re-select the mailbox			 
      (eucalyptus-imap-send-command-internal node
 					     (format "select \"%s\"" (plist-get node 'name))
 					     'eucalyptus-mailbox-select-response
 					     (list 'skip nil))
      ) ; end if
    ) ; end let

  ;; If you're showing a limited block of messages, this command will
  ;; be sent once we know how many messages there are in the box.
  (if (or (not (numberp (plist-get node 'limit))) (numberp oneline))
      (eucalyptus-imap-send-command-internal
       node
       (format "fetch %s (uid flags internaldate rfc822.size body.peek[header.fields (from subject)])"
	       (if oneline
		   (number-to-string oneline)
		 "1:*"
		 ) ; end if
	       ) ; end format
       'eucalyptus-mailbox-fetchenvelope-response
       (list 'mailbox-name (plist-get node 'name)
	     'oneline oneline)
       ) ; end send-command
    ) ; end if
  )

(defun eucalyptus-mailbox-select-response (status response data node originbuffer)
  "A response function for SELECT and EXAMINE commands."

  (if (string-match "^OK" status)
      (progn
	(plist-put (eucalyptus-imap-find-imap node) 'current-mailbox (plist-get data 'name))

	(if (and (numberp (plist-get node 'limit))
		 (not (plist-get data 'skip))
		 ) ; end and
	    (let ((oldbuf (current-buffer)) (buffer (generate-new-buffer "*select-temp*")) (exists))
	      (set-buffer buffer)
	      (insert response)
	      (beginning-of-buffer)
	      (if (re-search-forward "\\([0-9]+\\)[ 	]*exists" nil t)
		  (setq exists (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
		(set-buffer oldbuf)
		(kill-buffer buffer)
		(error "Improper format for a SELECT response")
		) ; end if we see the EXISTS message
	      
	      ;; re-send the command to be sure we're still looking at this mailbox
	      (let ((current-mailbox (plist-get (eucalyptus-imap-find-imap node) 'current-mailbox)))
		(if (and current-mailbox
			 (string-equal current-mailbox (plist-get node 'name))
			 (string-equal (process-status (plist-get (eucalyptus-imap-find-imap node) 'process)) "open")
			 ) ; end and
		    nil ; no need to re-select the mailbox			 
		  (eucalyptus-imap-send-command-internal node
							 (format "select \"%s\"" (plist-get node 'name))
							 'eucalyptus-mailbox-select-response
							 (list 'skip t))
		  ) ; end if
		) ; end let

	      ;; finally send the fetch command
	      (eucalyptus-imap-send-command-internal
	       node
	       (format "fetch %d:* (uid flags internaldate rfc822.size body.peek[header.fields (from subject)])"
		       (max 1 (1+ (- exists (plist-get node 'limit))))
		       ) ; end format
	       'eucalyptus-mailbox-fetchenvelope-response
	       (list 'mailbox-name (plist-get node 'name)
		     'oneline nil)
	       ) ; end send-command

	      (kill-buffer buffer)
	      ) ; end let
	  ) ; end if showing a limited block of messages

	) ; end progn
    (plist-put (eucalyptus-imap-find-imap node) 'current-mailbox nil)
    (error status)
    ) ; end if
  )

(defun eucalyptus-mailbox-generic-isselected (node)
  "A generic check to see that node's mailbox is currently selected by IMAP."

  (let ((current-mailbox (plist-get (eucalyptus-imap-find-imap node) 'current-mailbox)))
    (if (and current-mailbox
	     (string-equal current-mailbox (plist-get node 'name))
	     (string-equal (process-status (plist-get (eucalyptus-imap-find-imap node) 'process)) "open")
	     ) ; end and
	nil ; no need to re-select the mailbox			 
      (eucalyptus-imap-send-command-internal node
					     (format "select \"%s\"" (plist-get node 'name))
					     'eucalyptus-mailbox-select-response
					     (list 'skip t))
      ) ; end if
    ) ; end let
  )

(defun eucalyptus-mailbox-fetchenvelope-response (status response data node originbuffer)
  "A response function for envelope FETCH commands."
  
  (if (string-match "^OK" status)
      (let ((oldbuf (current-buffer))
	    (tmpbuffer (generate-new-buffer "*summary-temp*"))
	    (oneline (plist-get data 'oneline))
	    (line)
	    (messages nil))
	(if (numberp oneline) (setq line oneline) (setq line 1))

	(set-buffer tmpbuffer)
	(insert response)
	(beginning-of-buffer)
	(while (re-search-forward "^\\*[ 	]*\\([0-9]+\\)[ 	]*fetch[ 	]*" nil t)
	  (let (number flags uid internaldate size name email subject
		       start end valstart valend length)
	    (setq number (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))

	    (setq start (min (1+ (point)) (point-max)))
	    (if (re-search-forward "{\\([0-9]+\\)}$" nil t)
		(setq end (point-marker))
	      (error (format "Unexpected format for a FETCH response 1 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    (goto-char start)
	    (if (re-search-forward "flags[ 	]*" (marker-position end) t)
		(if (looking-at "()")
		    (setq flags nil)
		  (setq valstart (point))
		  (forward-sexp 1)
		  (setq valend (point-marker))
		  (goto-char valstart)
		  (while (re-search-forward "\\\\\\([-A-Za-z]+\\)" valend t)
		    (replace-match "\"\\1\""))
		  (setq flags (read (string-make-unibyte (buffer-substring valstart (marker-position valend)))))
		  ) ; end if just ()
	      (error (format "Unexpected format for a FETCH response 2 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    (goto-char start)
	    (if (re-search-forward "uid[ 	]+\\([0-9]+\\)" (marker-position end) t)
		(setq uid (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	      (error (format "Unexpected format for a FETCH response 3 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    (goto-char start)
	    (if (re-search-forward "internaldate[ 	]*" (marker-position end) t)
		(progn
		  (setq valstart (min (1+ (point)) (point-max)))
		  (forward-sexp 1)
		  (setq valend (max (1- (point)) (point-min)))
		  (setq internaldate (string-make-unibyte (buffer-substring valstart valend)))
		  ) ; end progn
	      (error (format "Unexpected format for a FETCH response 4 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    (goto-char start)
	    (if (re-search-forward "rfc822\\.size[ 	]+\\([0-9]+\\)" (marker-position end) t)
		(setq size (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	      (error (format "Unexpected format for a FETCH response 5 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if

	    (goto-char end)
	    (if (re-search-backward "{\\([0-9]+\\)}$" start t)
		(progn
		  (setq length (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
		  (goto-char end)
		  (setq start (point))

		  ;; becuase some characters may have more than one
		  ;; octal (such as DOS-inspired EOLNs), this may be
		  ;; an overestimate of the distance I want to go.
		  ;; That's okay.
		  (condition-case err
		      (forward-char length)
		    (error (end-of-buffer))
		    ) ; end condition-case

		  (setq end (point-marker))
		  ) ; end progn
	      (error (format "Unexpected format for a FETCH response 6 (see buffer \"%s\")"
			     (buffer-name tmpbuffer)))
	      ) ; end if
      
	    (goto-char start)
	    (if (re-search-forward "^From:[ 	]+\\(\"?\\)\\(.*[^ 	]\\)\\1[ 	]*<\\(.*@.*\\)>$"
				   (marker-position end) t)
		(progn
		  (setq name (string-make-unibyte (buffer-substring (match-beginning 2) (match-end 2))))
		  (setq email (string-make-unibyte (buffer-substring (match-beginning 3) (match-end 3))))
		  ) ; end progn
	      (goto-char start)
	      (if (re-search-forward "^From:[ 	]+\\(\"?\\)\\(.*[^ 	]\\)\\1$" (marker-position end) t)
		  (progn
		    (setq name (string-make-unibyte (buffer-substring (match-beginning 2) (match-end 2))))
		    (setq email nil)
		    ) ; end progn
		(setq name nil)
		(setq email nil)
		) ; end if
	      ) ; end if

	    (goto-char start)
	    (if (re-search-forward "^Subject:[ 	]+\\(.*\\)$" (marker-position end) t)
		(setq subject (string-make-unibyte (buffer-substring (match-beginning 1) (match-end 1))))
	      (setq subject nil)
	      ) ; end if
      
	    (setq messages (cons (list 'line line
				       'number number
				       'flags flags
				       'uid uid
				       'date internaldate
				       'size size
				       'name name
				       'email email
				       'subject subject
				       'selected nil)
				 messages)
		  ) ; end setq

	    (if (not (numberp oneline)) (setq line (1+ line)))

	    ) ; end let
	  ) ; end while

	(set-buffer oldbuf)
	(kill-buffer tmpbuffer)

	(if (numberp oneline)
	    (let ((i 0) (oldmess (plist-get node 'messages)) (newmess))
	      (while (< i (length oldmess))
		(if (= (plist-get (nth i oldmess) 'line) oneline)
		    (let ((thismess (car messages)))
		      (if (plist-get (nth i oldmess) 'selected)
			  (plist-put thismess 'selected t)
			) ; end if
		      (setq newmess (cons thismess newmess))
		      ) ; end let
		  (setq newmess (cons (nth i oldmess) newmess))
		  ) ; end if
		(setq i (1+ i))
		) ; end while
	      (plist-put node 'messages (nreverse newmess))
	      (eucalyptus-mailbox-draw node oneline)
	      ) ; end let

	  (plist-put node 'messages (nreverse messages))
	  (eucalyptus-mailbox-draw node)
	  ) ; end if

	) ; end let
    (error status)
    ) ; end if
  ) 

(defun eucalyptus-mailbox-draw (node &optional oneline)
  "Fill the summary buffer with message lines, or, if oneline is a
number, just redraw that line."
  
  (let ((oldbuf (current-buffer))
	(buffer (plist-get node 'buffer))
	(messages (plist-get node 'messages))
	(justemails (plist-get node 'justemails))
	(pointline) (pointcol))
    (set-buffer buffer)
    (setq pointline (count-lines 1 (min (1+ (point)) (point-max))))
    (setq pointcol (current-column))
    (setq buffer-read-only nil)

    (if (numberp oneline)
	(let ((i 0))
	  (beginning-of-buffer)
	  (end-of-line)
	  (while (and (< i (length messages))
		      (not (= (plist-get (nth i messages) 'line) oneline))
		      (< (point) (point-max))
		      ) ; end and
	    (setq i (1+ i))
	    (forward-char 1)
	    (end-of-line)
	    ) ; end while
	  (beginning-of-line)
	  (if (< i (length messages))
	      (let (start end)
		(setq start (point))
		(end-of-line)
		(setq end (point))
		(delete-region start end)
		(eucalyptus-mailbox-draw-line (nth i messages) justemails)
		) ; end end let
	    ) ; end if
	  ) ; end let

      (let ((i 0))
	(erase-buffer)
	(while (< i (length messages))
	  (eucalyptus-mailbox-draw-line (nth i messages) justemails)
	  (insert "\n")
	  (setq i (1+ i))
	  ) ; end while
	) ; end let

      ) ; end if

    (goto-line pointline)
    (move-to-column pointcol)

    (setq buffer-read-only t)
    (set-buffer oldbuf)
    ) ; end let
  )

(defun eucalyptus-mailbox-draw-line (message &optional justemails)
  "Draws one message line in the summary buffer."

  (let ((flags (plist-get message 'flags))
	(uid (plist-get message 'uid))
	(date (plist-get message 'date))
	(size (plist-get message 'size))
	(name (plist-get message 'name))
	(email (plist-get message 'email))
	(subject (plist-get message 'subject))
	(selected (plist-get message 'selected)))
    
    (let ((recent (member "Recent" flags))
	  (seen (member "Seen" flags))
	  (answered (member "Answered" flags))
	  (deleted (member "Deleted" flags)))
      (setq flags (format "%s%s"
			  (if (or recent (not seen)) (if recent "N" "n") " ")
			  (if (or answered deleted) (if answered "A" "D") " ")
			  ) ; end format
	    ) ; end setq
      ) ; end let

    (let ((day (substring date 0 2))
	  (month (substring date 3 6))
	  (year (substring date 9 11))
	  (time (substring date 12 17)))
      (setq date (format "%s %s'%s (%s)" day month year time))
      ) ; end let

    (if (and justemails (stringp email)) (setq name email))
    (if (stringp name)
	(if (> (length name) 25) (setq name (substring name 0 25)))
      (setq name "(none)")
      ) ; end if you have a name
    
    (setq size (round (/ (float size) 1024.)))

    (insert (format "%6d %s%s %s  %-25s (%3dK) %s" uid (if selected "X" " ") flags date name size subject))

    ) ; end let
  )

;;; message displays

(defun eucalyptus-mailbox-read-message ()
  "Read the selected message."
  (interactive)

  (let ((buffer (current-buffer)) (node))
    (setq node (eucalyptus-find-node buffer eucalyptus-tree))
    (if (or (not node) (not (string-equal (plist-get node 'type) "SUMMARY")))
	(error "This is not a summary buffer")
      (let ((line (count-lines 1 (min (1+ (point)) (point-max))))
	    (messages (plist-get node 'messages)) (i 0) (uid) (number))
	(while (and (< i (length messages))
		    (not (= (plist-get (nth i messages) 'line) line))
		    ) ; end and
	  (setq i (1+ i))
	  ) ; end while
	(if (< i (length messages)) (setq uid (plist-get (nth i messages) 'uid))
	  (error "There is something wrong with the format of this summary buffer"))
	(setq number (plist-get (nth i messages) 'number))

	(let ((imap-node (eucalyptus-imap-find-imap node)))
	  (let ((messagebuf (generate-new-buffer (format "MESSAGE: %s in %s (%s@%s:%d)"
							 uid
							 (plist-get node 'name)
							 (plist-get imap-node 'username)
							 (plist-get imap-node 'hostname)
							 (plist-get imap-node 'port)
							 ) ; end format
						 ) ; end generate-new-buffer
			    )
		(message-node))
	    (switch-to-buffer messagebuf)
	    ; (eucalyptus-message-mode)
	    (insert "\n\n	 Reading message headers and structure from server...\n\n")
	    (beginning-of-buffer)
	    (setq buffer-read-only t)

	    (setq message-node (list 'children nil
				     'buffer messagebuf
				     'type "MESSAGE"
				     'number number
				     'uid uid
				     'fields nil
				     'header nil
				     'headerstart nil
				     'headerend nil
				     'structure nil
				     'processes nil
				     ))
	    (eucalyptus-add-child (plist-get node 'buffer) message-node)

	    ;; be sure we're still connected to the right mailbox
	    (eucalyptus-mailbox-generic-isselected node)

	    (eucalyptus-imap-send-command-internal
	     message-node (format
		   "uid fetch %d (body body[header.fields (date from sender reply-to subject to cc bcc)] body[header])"
		   uid) ; end format
	     'eucalyptus-message-structure-response
	     (list 'uid uid)
	     ) ; end send-command
	    ) ; end let messagebuf, message-node
	  ) ; end let imap-node
	) ; end let line, messages, uid
      ) ; end if summary buffer
    ) ; end let buffer
  )

(defun eucalyptus-message-structure-response (status response data node originbuffer)
  "A response function for message structure."

  (if (string-match "^OK" status)
      (let ((oldbuf (current-buffer))
	    (tmpbuf (generate-new-buffer "*message-temp*"))
	    (buffer (plist-get node 'buffer))
	    (start) (end) (structure) (which) (i)
	    (fields) (header))
	(set-buffer tmpbuf)
	(insert response)
	(beginning-of-buffer)
	(if (not (re-search-forward "fetch[ 	]*(" nil t))
	    (error (format "Unexpected FETCH response format 1, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(if (not (re-search-forward "body[ 	]*(" nil t))
	    (error (format "Unexpected FETCH response format 2, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(backward-char 1)
	(setq start (point))
	(forward-sexp 1)
	(setq end (point-marker))

	(goto-char start)
	(while (search-forward "nil" (marker-position end) t)
	  (replace-match "'none" t))

	(goto-char start)
	(while (search-forward ")(" (marker-position end) t)
	  (replace-match ") (" t))

	(setq structure (read (string-make-unibyte (buffer-substring start (marker-position end)))))

	(goto-char end)
	(if (not (search-forward "body[header" nil t))
	    (error (format "Unexpected FETCH response format 3, see buffer \"%s\""
			   (buffer-name tmpbuf))))

	(if (looking-at "\\.fields") (setq which 'fields) (setq which 'header))

	(if (not (re-search-forward "{\\([0-9]+\\)}$" nil t))
	    (error (format "Unexpected FETCH response format 4, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(setq i (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	(if (= (point) (point-max))
	    (error (format "Unexpected FETCH response format 5, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(forward-char 1)
	(setq start (point))
	(while (> i 0)
	  (if (looking-at "$") (setq i (- i 2)) (setq i (1- i)))
	  (if (= (point) (point-max))
	      (error (format "Unexpected FETCH response format 6, see buffer \"%s\""
			     (buffer-name tmpbuf))))
	  (forward-char 1)
	  )
	(setq end (point))

	;; note the missing `q'!!! `which' evaluates the the
	;; appropriate quoted symbol
	(set which (string-make-unibyte (buffer-substring start end)))

	(if (not (search-forward "body[header" nil t))
	    (error (format "Unexpected FETCH response format 7, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(if (not (re-search-forward "{\\([0-9]+\\)}$" nil t))
	    (error (format "Unexpected FETCH response format 8, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(setq i (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	(if (= (point) (point-max))
	    (error (format "Unexpected FETCH response format 9, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(forward-char 1)
	(setq start (point))
	(while (> i 0)
	  (if (looking-at "$") (setq i (- i 2)) (setq i (1- i)))
	  (if (= (point) (point-max))
	      (error (format "Unexpected FETCH response format 10, see buffer \"%s\""
			     (buffer-name tmpbuf))))
	  (forward-char 1)
	  )
	(setq end (point))

	;; another `set' construction
	(set (if (eq which 'fields) 'header 'fields)
	     (string-make-unibyte (buffer-substring start end)))

	(plist-put node 'fields fields)
	(plist-put node 'header header)

	(set-buffer buffer)
	(kill-buffer tmpbuf)

	(let ((pointline (count-lines 1 (min (1+ (point)) (point-max))))
	      (pointcol (current-column)))
	  (setq buffer-read-only nil)
	  (erase-buffer)
	  (plist-put node 'headerstart (point-marker))
	  (insert fields)
	  (plist-put node 'headerend (point-marker))
	  (eucalyptus-message-draw-part structure nil node)
	  (plist-put node 'structure (nreverse (plist-get node 'structure)))
	  (goto-line pointline)
	  (move-to-column pointcol)
	  (setq buffer-read-only t)
	  ) ; end let

	;; ask for the easy things--- text/plain and text/html
	(let ((i 0) (struct (plist-get node 'structure)))
	  (while (< i (length struct))
	    (if (and (string-match "text" (plist-get (nth i struct) 'content))
		     (string-match "plain" (plist-get (nth i struct) 'type)))
 		(eucalyptus-imap-send-command-internal node
 						       (format "uid fetch %d (body[%s])"
 							       (plist-get data 'uid)
 							       (plist-get (nth i struct) 'number))
 						       'eucalyptus-message-text-plain-response
 						       (list 'part i) nil t)
	      ) ; end if
	    (if (and (string-match "text" (plist-get (nth i struct) 'content))
		     (string-match "html" (plist-get (nth i struct) 'type)))
 		(eucalyptus-imap-send-command-internal node
 						       (format "uid fetch %d (body[%s])"
 							       (plist-get data 'uid)
 							       (plist-get (nth i struct) 'number))
 						       'eucalyptus-message-text-html-response
 						       (list 'part i) nil t)
	      ) ; end if
	    (setq i (1+ i))
	    ) ; end while
	  ) ; end let

	(set-buffer oldbuf)
	) ; end let
    (error status)
    ) ; end if
  )

(defun eucalyptus-message-draw-part (structure number node)
  "Draws a MIME part indicator for each part and subpart of a message
and conses a plist to node'structure for later use."

   (if (< (length structure) 2)
       (error (format "Unexpected BODY structure format 1: %s" (prin1-to-string structure))))

  (if (and (stringp (nth 0 structure)) (stringp (nth 1 structure)))
      (if (and (string-match "^message$" (nth 0 structure))
	       (string-match "^rfc822$" (nth 1 structure))
	       ) ; end and
	  (let ((i 0) (size) (struct (plist-get node 'structure)) (newelt (list 'start (point-marker))) (newnum))
	    (insert (make-string (* (length number) 4) ? ))
	    (insert "[MIME Part ")
	    (if (null number)
		(progn (insert "1.") (setq newnum "1."))
	      (while (< i (length number))
		(insert (format "%d." (nth i number)))
		(setq newnum (concat newnum (format "%d." (nth i number))))
		(setq i (1+ i))
		) ; end while
	      ) ; end if
	    (setq newnum (substring newnum 0 -1)) ; take off that last "."

 	    (if (< (length structure) 9)
 		(error (format "Unexpected BODY structure format 2: %s" (prin1-to-string structure))))

 	    (if (not (numberp (nth 6 structure)))
 		(error (format "Unexpected BODY structure format 3: %s" (prin1-to-string structure))))
	    (setq size (round (/ (float (nth 6 structure)) 1024.)))

 	    (if (not (stringp (nth 5 structure)))
 		(error (format "Unexpected BODY structure format 4: %s" (prin1-to-string structure))))

	    (let ((substructure (nth 8 structure)) (j 0) (subnumber 1))
	      (if (and (stringp (nth 0 substructure)) (stringp (nth 1 substructure)))
		  ;; the contents of this MESSAGE/RFC822 is a single Content/type
		  (progn
  		    (insert (format " Content-type %s/%s, %dK \"%s\"]\n"
  				    (nth 0 structure) (nth 1 structure) size (nth 5 structure)))
		    (plist-put newelt 'end (point-marker))
		    (insert "\n")
		    (plist-put newelt 'number newnum)
		    (plist-put newelt 'content (nth 0 structure))
		    (plist-put newelt 'type (nth 1 structure))
		    (plist-put newelt 'size size)
		    (plist-put newelt 'encoding (nth 5 structure))
		    (plist-put newelt 'misc nil)
		    (plist-put node 'structure (cons newelt struct))
		    (eucalyptus-message-draw-part substructure (append number (list 1)) node)
		    ) ; end progn
		
		;; the contents of this MESSAGE/RFC822 is a structure type
 		(if (not (stringp (nth (1- (length substructure)) substructure)))
 		    (error (format "Unexpected BODY structure format 5: %s" (prin1-to-string structure))))
		
  		(insert (format " Content-type %s/%s, %dK \"%s\" %s]\n"
  				(nth 0 structure) (nth 1 structure) size (nth 5 structure)
  				(nth (1- (length substructure)) substructure)))
		(plist-put newelt 'end (point-marker))
		(insert "\n")
		(plist-put newelt 'number newnum)
		(plist-put newelt 'content (nth 0 structure))
		(plist-put newelt 'type (nth 1 structure))
		(plist-put newelt 'size size)
		(plist-put newelt 'encoding (nth 5 structure))
		(plist-put newelt 'misc (nth (1- (length substructure)) substructure))
		(plist-put node 'structure (cons newelt struct))
		(while (< j (1- (length substructure)))
 		  (if (not (listp (nth j substructure)))
 		      (error (format "Unexpected BODY structure format 6: %s" (prin1-to-string structure))))
		  (eucalyptus-message-draw-part (nth j substructure) (append number (list subnumber)) node)
		  
		  (setq subnumber (1+ subnumber))
		  (setq j (1+ j))
		  ) ; end while
		) ; end if contents are simple or complicated
	      ) ; end let substructure

	    ) ; end let

	;; if some CONTENT/TYPE != MESSAGE/RFC822
	(let ((i 0) (size) (struct (plist-get node 'structure)) (newelt (list 'start (point-marker))) (newnum))
	  (insert (make-string (* (length number) 4) ? ))
	  (insert "[MIME Part ")
	  (if (null number)
	      (progn (insert "1.") (setq newnum "1."))
	    (while (< i (length number))
 	      (insert (format "%d." (nth i number)))
 	      (setq newnum (concat newnum (format "%d." (nth i number))))
	      (setq i (1+ i))
	      ) ; end while
	    ) ; end if
	  (setq newnum (substring newnum 0 -1)) ; take off that last "."

 	  (if (< (length structure) 7)
 	      (error (format "Unexpected BODY structure format 7: %s" (prin1-to-string structure))))

 	  (if (not (numberp (nth 6 structure)))
 	      (error (format "Unexpected BODY structure format 8: %s" (prin1-to-string structure))))
	  (setq size (round (/ (float (nth 6 structure)) 1024.)))

 	  (if (not (stringp (nth 5 structure)))
 	      (error (format "Unexpected BODY structure format 9: %s" (prin1-to-string structure))))
		
	  (plist-put newelt 'number newnum)
	  (plist-put newelt 'content (nth 0 structure))
	  (plist-put newelt 'type (nth 1 structure))
	  (plist-put newelt 'size size)
	  (plist-put newelt 'encoding (nth 5 structure))
	  (plist-put newelt 'misc nil)
  	  (if (equal (nth 2 structure) '(quote none))
  	      (insert (format " Content-type %s/%s, %dK \"%s\"]\n"
  			      (nth 0 structure) (nth 1 structure) size (nth 5 structure)))
  	    (insert (format " Content-type %s/%s, %dK \"%s\" %s]\n"
  			    (nth 0 structure) (nth 1 structure) size (nth 5 structure)
  			    (prin1-to-string (nth 2 structure))))
  	    (plist-put newelt 'misc (prin1-to-string (nth 2 structure)))
  	    ) ; end if
	  (plist-put newelt 'end (point-marker))
	  (insert "\n")
	  (plist-put node 'structure (cons newelt struct))
	  ) ; end let
	) ; end if type (MESSAGE/RFC822 or otherwise)

    ;; if not a CONTENT/TYPE, it's probably a (list, list, list, list, TYPE)
    (let ((subnumber 1) (i 0) (j 0))
        (if (not (stringp (nth (1- (length structure)) structure)))
  	  (error (format "Unexpected BODY structure format 10: %s" (prin1-to-string structure))))

      (insert (make-string (* (length number) 4) ? ))
       (insert (format "[MIME Structure %s]\n\n" (nth (1- (length structure)) structure)))

      (while (< j (1- (length structure)))
 	(if (not (listp (nth j structure)))
 	  (error (format "Unexpected BODY structure format 11: %s" (prin1-to-string structure))))
	(eucalyptus-message-draw-part (nth j structure) (append number (list subnumber)) node)
	
	(setq subnumber (1+ subnumber))
	(setq j (1+ j))
	) ; end while
      ) ; end let
    ) ; end if
  )

(defun eucalyptus-message-text-plain-response (status response data node originbuffer)
  "A response function for reading text/plain message parts."
  (if (string-match "^OK" status)
      (let ((oldbuf (current-buffer)) (tmpbuf (generate-new-buffer "*message-temp*"))
	    (empty) (skipchars) (start) (end) (text)
	    (info (nth (plist-get data 'part) (plist-get node 'structure))))
	(set-buffer tmpbuf)
	(insert response)
	(beginning-of-buffer)
	(if (not (re-search-forward "{\\([0-9]+\\)}$" nil t))
	    (if (re-search-forward "body\\[[0-9]+\\][ 	]+\"\"" nil t)
		(setq empty t)
	      (error (format "Unexpected FETCH text/plain response format 1, see buffer \"%s\""
			     (buffer-name tmpbuf)))
	      ) ; end if we see body[#] ""
	  ) ; end if we see {##}
	(if empty
	    (setq text "")
	  (setq skipchars (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	  (if (= (point) (point-max))
	      (error (format "Unexpected FETCH text/plain response format 2, see buffer \"%s\""
			     (buffer-name tmpbuf))))
	  (forward-char 1)
	  (setq start (point))
	  (while (> skipchars 0)
	    (if (looking-at "$") (setq skipchars (- skipchars 2)) (setq skipchars (1- skipchars)))
	    (if (= (point) (point-max))
		(error (format "Unexpected FETCH text/plain response format 3, see buffer \"%s\""
			       (buffer-name tmpbuf))))
	    (forward-char 1)
	    )
	  (setq end (point))
	  (setq text (string-make-unibyte (buffer-substring start end)))
	  ) ; end if empty
	(set-buffer (plist-get node 'buffer))
	(kill-buffer tmpbuf)
	(setq buffer-read-only nil)
	(save-excursion
	  (goto-char (plist-get info 'start))
	  (if (not (re-search-forward "MIME Part" nil t))
	      (error "Someone's been fooling with this buffer!")
	    ) ; end if
	  (goto-char (match-beginning 0))
	  (insert "DOWNLOADED ")
	  (goto-char (plist-get info 'end))
	  (insert "\n")
	  (insert text)
	  (plist-put info 'end (point-marker))
	  ) ; end save-excursion
	(setq buffer-read-only t)
	(set-buffer oldbuf)
	) ; end let
    (error status)
    ) ; end if
  )

(defun eucalyptus-message-text-html-response (status response data node originbuffer)
  "A response function for reading text/html message parts."
  (if (string-match "^OK" status)
      (let ((oldbuf (current-buffer)) (tmpbuf (generate-new-buffer "*message-temp*"))
	    (fillwidth) (skipchars) (start) (end) (text) (filename) (lynx)
	    (info (nth (plist-get data 'part) (plist-get node 'structure))))
	(set-buffer (plist-get node 'buffer))
;	(setq fillwidth fill-column)
	(setq fillwidth (window-width))
	(set-buffer tmpbuf)
	(insert response)
	(beginning-of-buffer)
	(if (not (re-search-forward "{\\([0-9]+\\)}$" nil t))
	    (error (format "Unexpected FETCH text/html response format 1, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(setq skipchars (string-to-number (buffer-substring (match-beginning 1) (match-end 1))))
	(if (= (point) (point-max))
	    (error (format "Unexpected FETCH text/html response format 2, see buffer \"%s\""
			   (buffer-name tmpbuf))))
	(forward-char 1)
	(setq start (point))
	(while (> skipchars 0)
	  (if (looking-at "$") (setq skipchars (- skipchars 2)) (setq skipchars (1- skipchars)))
	  (if (= (point) (point-max))
	      (error (format "Unexpected FETCH text/html response format 3, see buffer \"%s\""
			     (buffer-name tmpbuf))))
	  (forward-char 1)
	  )
	(setq end (point))
	(setq filename (format "%s/message%d-%s.html" eucalyptus-tmp-directory
			       (plist-get node 'uid) (random 1000000)))
	(condition-case err
	    (write-region start end filename)
	  (error (error (format "Cannot write to file %s" filename))))

	(setq lynx (start-process (format "%s %s" eucalyptus-lynx filename) (plist-get node 'buffer)
				  eucalyptus-lynx "-dump" (format "-width=%d" fillwidth) filename))
	(set-process-filter lynx 'eucalyptus-message-text-html-filter)
	(set-process-sentinel lynx 'eucalyptus-message-text-html-sentinel)
	(plist-put node 'processes (cons (list 'which lynx 'file filename) (plist-get node 'processes)))

	(set-buffer (plist-get node 'buffer))
	(kill-buffer tmpbuf)
	(setq buffer-read-only nil)
	(save-excursion
	  (goto-char (plist-get info 'start))
	  (if (not (re-search-forward "MIME Part" nil t))
	      (error "Someone's been fooling with this buffer!")
	    ) ; end if
	  (goto-char (match-beginning 0))
	  (insert "DOWNLOADED ")
	  (goto-char (marker-position (plist-get info 'end)))
	  (insert "\n")
	  (set-marker (process-mark lynx) (point))
	  ) ; end save-excursion
	(setq buffer-read-only t)
	(set-buffer oldbuf)
	) ; end let
    (error status)
    ) ; end if
  )

(defun eucalyptus-message-text-html-filter (process output)
  "This completes the job of html conversion by putting the formatted
text into the message buffer."

  (let ((oldbuf (current-buffer)))
    (set-buffer (process-buffer process))
    (setq buffer-read-only nil)
    (save-excursion
      (goto-char (process-mark process))
      (insert output)
      (set-marker (process-mark process) (point))
      ) ; end save-excursion
    (setq buffer-read-only t)
    (set-buffer oldbuf)
    ) ; end let
  )

(defun eucalyptus-message-text-html-sentinel (process event)
  "This completely completes the job of html conversion by deleting
the temporary file."

  (let ((processes (plist-get (eucalyptus-find-node (process-buffer process) eucalyptus-tree) 'processes))
	(i 0))
    (while (and (< i (length processes))
		(not (eq (plist-get (nth i processes) 'which) process))
		) ; end and
      (setq i (1+ i))
      ) ; end while
    (if (= i (length processes))
	(error (format "The process \"%s\" is missing from the process list: %s"
		       (process-name process) (prin1-to-string processes)))
      ) ; end if
    (condition-case err
	(delete-file (plist-get (nth i processes) 'file))
      (error (error (format "Couldn't delete temporary file \"%s\"" (plist-get (nth i processes) 'file))))
      ) ; end condition-case

    ) ; end let
  )
