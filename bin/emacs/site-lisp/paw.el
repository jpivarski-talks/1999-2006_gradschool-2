;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;  This paw.el defines paw-mode v. 1.3.1   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                           ;;;
;;;  Put this paw.el file into your ~/bin directory (or somewhere),           ;;;
;;;  and include a line like:                                                 ;;;
;;;      (load-file "~/bin/paw.el")                                           ;;;
;;;  in your `.emacs' (or `.xemacs/init.el') file.                            ;;;
;;;                                                                           ;;;
;;;  If you want to make it run (slightly) faster, byte compile it:           ;;;
;;;      M-x byte-compile-file RET ~/bin/paw.el                               ;;;
;;;  And include:                                                             ;;;
;;;      (load-file "~/bin/paw.elc")                                          ;;;
;;;  instead.                                                                 ;;;
;;;                                                                           ;;;
;;;  `paw-mode' will be automatically invoked on all .kumac files,            ;;;
;;;  but you can start it explicitly on an existing buffer with:              ;;;
;;;      M-x paw-start   (a.k.a. control-c control-n)                         ;;;
;;;  or on a new (temporary) buffer with:                                     ;;;
;;;      M-x paw                                                              ;;;
;;;  (The temporary buffer may be later saved.)                               ;;;
;;;                                                                           ;;;
;;;  The keystroke control-j (or meta-RET) evaluates a line; the output       ;;;
;;;  goes into the buffer "*[buffer-name] PAW output*" and                    ;;;
;;;  "*[buffer-name] PAW log*" (more permanantly).  If you don't want to      ;;;
;;;  overwrite the contents of the output buffer, type a control-u            ;;;
;;;  just before the control-j.  Control-c control-w executes a region by     ;;;
;;;  saving it to a temporary kumac file.                                     ;;;
;;;                                                                           ;;;
;;;  The keystroke control-c control-a (two keys) sends the ever-popular      ;;;
;;;  SIGINT.                                                                  ;;;
;;;                                                                           ;;;
;;;  Here are some things to define in your .pawlogon.kumac to make PAW       ;;;
;;;  more Emacs-friendly:                                                     ;;;
;;;      kuip/set/host_pager 'cat'  (passes help system control to Emacs)     ;;;
;;;      kuip/set/columns 65        (sets the output column width)            ;;;
;;;                                                                           ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;  USER VARIABLES   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defvar paw-command-line "/nfs/cern/pro/bin/pawX11"
  "The UNIX path to the PAW command.")

(defvar paw-temporary-directory "/tmp"
  "The UNIX path to a directory where Emacs can create temporary files.")

(defvar paw-initial-keysequence "\n"
  "That which is typed by default, at the beginning of every PAW session.")

(defvar paw-start-process 'ask
  "If nil, you will have to `paw-start' (C-c C-n) on your own.  If
'ask, you will be prompted. If 'always, a PAW session will always
start up in paw-mode.")

(defvar paw-popup-output t
  "If t, paw-start will pop-up a window displaying the output of commands.")

(defvar paw-help-takes-over t
  "If t, entering the PAW help system makes the output buffer your
only window (so you can read and scroll it with `scroll-other-window'
from the minibuffer).  The previous window configuration is restored
when you get to a leaf in the help tree.")

;;;  INTERNAL VARIABLES   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(provide 'paw)

(setq auto-mode-alist (append '(("\\.kumac\\'" . paw-mode)) auto-mode-alist))

(defvar paw-mode-map () "Keymap used in paw-mode buffers.")
(if (not paw-mode-map)
    (progn
      (setq paw-mode-map (make-sparse-keymap))
      (define-key paw-mode-map "\C-j" 'paw-execute-line)
      (define-key paw-mode-map "\M-\C-m" 'paw-execute-line)
      (define-key paw-mode-map "\C-c\C-w" 'paw-execute-region)
      (define-key paw-mode-map "\C-c:" 'paw-execute)
      (define-key paw-mode-map "\C-c\C-c" 'paw-execute)
      (define-key paw-mode-map "\C-c\C-a" 'paw-abort-command)

      (define-key paw-mode-map "\C-c\C-n" 'paw-start)
      (define-key paw-mode-map "\C-c\C-k" 'paw-kill)
      (define-key paw-mode-map "\C-c\C-p" 'paw-split-work)
      (define-key paw-mode-map "\C-c\C-o" 'paw-split-output)
      (define-key paw-mode-map "\C-c\C-l" 'paw-split-log)
      ) ; end progn
  ) ; end if

(defvar paw-log-mode-map () "Keymap used in paw-mode buffers.")
(if (not paw-log-mode-map)
    (progn
      (setq paw-log-mode-map (make-sparse-keymap))
      (define-key paw-log-mode-map "\C-c:" 'paw-execute)
      (define-key paw-log-mode-map "\C-c\C-c" 'paw-execute)
      (define-key paw-log-mode-map "\C-c\C-a" 'paw-abort-command)

      (define-key paw-log-mode-map "\C-c\C-n" 'paw-start)
      (define-key paw-log-mode-map "\C-c\C-k" 'paw-kill)
      (define-key paw-log-mode-map "\C-c\C-p" 'paw-split-work)
      (define-key paw-log-mode-map "\C-c\C-o" 'paw-split-output)
      (define-key paw-log-mode-map "\C-c\C-l" 'paw-split-log)
      ) ; end progn
  ) ; end if

(defvar paw-mode-abbrev-table nil "Abbrev table used in paw-mode buffers.")

(defvar paw-mode-syntax-table nil "Syntax table used in paw-mode buffers.")
(if (not paw-mode-syntax-table)
    (progn
      (setq paw-mode-syntax-table (make-syntax-table))
      (modify-syntax-entry ?\' "\"" paw-mode-syntax-table)
      (modify-syntax-entry ?/ "_")
      (define-abbrev-table 'paw-mode-abbrev-table ())
      ) ; end progn
  ) ; end if

(defvar paw-font-lock-keywords
  '(
    ("^[ \t]*\\(\\*.*\\)$" 1 font-lock-comment-face)
    ("\"[^\"]+\"" . font-lock-string-face)
    ("'[^']+'" . font-lock-string-face)
    ("^[ \t]*\\([^ \t\\*][^ \t]*\\)" 1 font-lock-keyword-face)
    ("\\(\\$[^( \t]+\\)(" 1 font-lock-function-name-face)
    )
  )

(defvar paw-log-font-lock-keywords
  '(
    ("^[ \t]*\\(\\*.*\\)$" 1 font-lock-comment-face)
    ("\"[^\"]+\"" . font-lock-string-face)
    ("'[^']+'" . font-lock-string-face)
    ("^\\(PAW >\\)[ \t]*\\([^ \t]*\\)" (1 font-lock-warning-face) (2 font-lock-keyword-face))
    ("^PAW >" . font-lock-warning-face)
    ("^----> .*$" . font-lock-warning-face)
    )
  )

(defvar paw-history nil "History of PAW commands entered in the minibuffer.")
(defvar paw-query-history nil "History of responses to PAW queries.")

(defvar paw-status nil "This is just to avoid compilation warnings---
it's really a local variable, local to the buffer running paw-mode.")

;;;  USER FUNCTIONS   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun paw-mode ()
  "Major mode for editing paw commands and `.kumac' files in Emacs.
If you execute this as a command, your current buffer will be
interpreted as a PAW buffer from which you can execute lines of code.
If you would rather start a new PAW buffer, type M-x paw (which
creates a new `tmp.kumac', unassociated with a file until you save) or
visit a file (C-x C-f) with a `.kumac' suffix.

Commands:
\\{paw-mode-map}"
  (interactive)

  (kill-all-local-variables)
  (use-local-map paw-mode-map)

  (setq major-mode 'paw-mode)
  (setq mode-name "PAW")

  (make-local-variable 'paw-status)
  (setq paw-status "no process")
  (setq mode-line-process '(":" paw-status))

  (setq local-abbrev-table paw-mode-abbrev-table)
  (set-syntax-table paw-mode-syntax-table)
  
  (make-local-variable 'comment-start)
  (setq comment-start "*")
  (make-local-variable 'comment-end)
  (setq comment-end "")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "^[ \t]*\\*")

  (make-local-variable 'paragraph-start)
  (setq paragraph-start "\f\\|[ \t]*$")
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate paragraph-start)

  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults '(paw-font-lock-keywords t))

  (make-local-variable 'indent-line-function)
  (setq indent-line-function 'paw-indent-line)

  (if (not (paw-find-node 'workbuffer (current-buffer)))
      (progn
	(if (eq paw-start-process 'always) (paw-start))
	(if (and (eq paw-start-process 'ask)
		 (y-or-n-p "Start a PAW process? "))
	    (paw-start))
	) ; end progn
    ) ; end if

  )

(defun paw-log-mode ()
  "Major mode for displaying PAW output.  Each PAW session will have
an output buffer and a cumulative log buffer (named `*PAW-out:
your.kumac*' and `*PAW-log: your.kumac*<n>'), and they use
`paw-log-mode', mostly just for syntax coloring.  `paw-log-mode'
provides some functionality to these buffers, but commands for
restarting and killing PAW sessions have only been fully tested from
the work buffer.

Nevertheless... commands:
\\{paw-log-mode-map}"
  (interactive)

  (kill-all-local-variables)
  (use-local-map paw-log-mode-map)

  (setq major-mode 'paw-log-mode)
  (setq mode-name "PAW output")

  (setq local-abbrev-table paw-mode-abbrev-table)
  (set-syntax-table paw-mode-syntax-table)

  (make-local-variable 'comment-start)
  (setq comment-start "*")
  (make-local-variable 'comment-end)
  (setq comment-end "")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "^[ \t]*\\*")

  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults '(paw-log-font-lock-keywords t))
  )

(defvar paw-process-list () "List of PAW processes, each associated with a buffer.")

(defun paw ()
  "Start a new PAW process with a `tmp.kumac' buffer.  This buffer
won't be associated with any file by default, so if you like your
work, you'll need to explicitly save it.  This function is provided so
that you don't always have to name your PAW sessions or associate them
with specific files.  Sometimes you just want to try something
quickly."
  (interactive)
  (let ((tmp paw-start-process))
    (setq paw-start-process nil)
    (switch-to-buffer (generate-new-buffer "tmp.kumac"))
    (paw-mode)
    (paw-start)
    (setq paw-start-process tmp)
    ) ; end let
  )

(defun paw-split (buffer-label)
  "Put some buffer in the other window."
  
  (let (buffer)
    (setq buffer (plist-get (paw-find-node 'workbuffer (current-buffer)) buffer-label))
    (if (null buffer)
	(setq buffer (plist-get (paw-find-node 'outputbuffer (current-buffer)) buffer-label)))
    (if (null buffer)
	(setq buffer (plist-get (paw-find-node 'logbuffer (current-buffer)) buffer-label)))
    (if (and (bufferp buffer) (buffer-live-p buffer))
	(save-excursion
	  (if (one-window-p) (split-window))
	  (other-window 1)
	  (if (not (eq buffer (current-buffer))) (switch-to-buffer buffer))
	  (other-window -1)
	  ) ; end save-excursion
      (cond ((eq buffer-label 'workbuffer) (error "The work buffer has been killed"))
	    ((eq buffer-label 'outputbuffer) (error "The output buffer has been killed"))
	    ((eq buffer-label 'logbuffer) (error "The cumulative log buffer has been killed"))
	    ) ; end cond
      ) ; end if
    ) ; end let
  )
(defun paw-split-work ()
  "Put the work buffer in the other window.  Most interaction will be
from the work buffer, so this function is provided in case you get
lost in a maze of buffers."
  (interactive)
  (paw-split 'workbuffer)
  )

(defun paw-split-output ()
  "Put the output buffer in the other window.  It's always wise to
keep an eye on the textual output of your commands, this is provided
as a quick way to see them."
  (interactive)
  (paw-split 'outputbuffer)
  )

(defun paw-split-log ()
  "Put the log buffer in the other window.  The log buffer is
cumulative: no output is overwritten in a PAW session.  Therefore,
this buffer is useful for debugging your session: to find out if you
inappropriately set some variable a long time ago which is screwing up
your plots now."
  (interactive)
  (paw-split 'logbuffer)
  )

(defun paw-start ()
  "Start a new PAW process, and associate it with this buffer.  If
there's already a PAW process associated with this buffer, `paw-start'
will ask you if you want to kill it and restart.  This is often a good
thing; it clears whatever variables you might have inappropriately set
and you can re-execute your final lines of code, confident that there
are no hidden dependencies."
  (interactive)

  (let ((node (paw-find-node 'workbuffer (current-buffer))))
    (if (null node) (setq node (paw-find-node 'outputbuffer (current-buffer))))
    (if (null node) (setq node (paw-find-node 'logbuffer (current-buffer))))
    (if node
	(if (yes-or-no-p "Kill existing PAW process? ")
	    (let ((outputbuffer (plist-get node 'outputbuffer))
		  (logbuffer (plist-get node 'logbuffer)))
	      (if (processp (plist-get node 'process)) (kill-process (plist-get node 'process)))
	      
	      (if (and (bufferp outputbuffer) (buffer-live-p outputbuffer))
		  (save-excursion
		    (set-buffer outputbuffer)
		    (goto-char (point-max))
		    (insert "----> PAW killed by user")
		    ) ; end save-excursion
		) ; end if
	      
	      (if (and (bufferp logbuffer) (buffer-live-p logbuffer))
		  (save-excursion
		    (set-buffer logbuffer)
		    (goto-char (point-max))
		    (setq buffer-read-only nil)
		    (insert "----> PAW killed by user")
		    (setq buffer-read-only t)
		    ) ; end save-excursion
		) ; end if
	      
	      (save-excursion
		(set-buffer (plist-get node 'workbuffer))
		(setq paw-status "no process")
		) ; end save-excursion
	      
	      (setq paw-process-list (delete node paw-process-list))
	      ) ; end let
	  (error "Can't attach two PAW processes to the same buffer")
	  ) ; end if we want to kill
      ) ; end if we see a node
    ) ; end let

  ; get into paw-mode
  (if (not (eq major-mode 'paw-mode)) (paw-mode))

  (let (workbuffer logbuffer outputbuffer process node)
    (setq paw-status "init")
    (message (format "Starting PAW with %s..." paw-command-line))

    (setq workbuffer (current-buffer))
    (setq logbuffer (generate-new-buffer (format "*PAW-log: %s*" (buffer-name workbuffer))))
    (setq outputbuffer (get-buffer-create (format "*PAW-out: %s*" (buffer-name workbuffer))))

    (save-excursion
      (set-buffer outputbuffer)
      (paw-log-mode)
      (setq truncate-lines t)
      (erase-buffer)
      ) ; end save-excursion

    (save-excursion
      (set-buffer logbuffer)
      (paw-log-mode)
      (setq buffer-read-only t)
      ) ; end save-excursion

    (setq process (start-process (format "PAW: %s" (buffer-name workbuffer)) nil paw-command-line))
    (set-process-filter process 'paw-filter)
    (set-process-sentinel process 'paw-sentinel)
    (process-send-string process paw-initial-keysequence)

    (setq node (list 'commands (list (list 'input ""))
		     'workbuffer workbuffer
		     'logbuffer logbuffer
		     'outputbuffer outputbuffer
		     'process process
		     'query-prompt nil
		     'window-configuration nil
		     )) ; end setq

    (setq paw-process-list (cons node paw-process-list))
    (if paw-popup-output (paw-split-output))

    ) ; end let
  )

(defun paw-kill ()
  "This kills an associated PAW process and, optionally, its
associated buffers.  It then goes into cleanup-mode, checking for
possible old buffers associated with PAW processes long dead.  Without
this, your buffer list can get to be overwhelming."
  (interactive)

  (let ((oldbuf (current-buffer))
	(node (paw-find-node 'workbuffer (current-buffer)))
	(try-to-kill-old-outputs t)
	(count 0)
;	(oldconf (current-window-configuration))
	)
    (delete-other-windows)
    (if (null node) (setq node (paw-find-node 'outputbuffer (current-buffer))))
    (if (null node) (setq node (paw-find-node 'logbuffer (current-buffer))))
    (if node
	(if (y-or-n-p "Kill PAW process? ")
	    (let ((outputbuffer (plist-get node 'outputbuffer))
		  (logbuffer (plist-get node 'logbuffer)))
	      (if (processp (plist-get node 'process)) (kill-process (plist-get node 'process)))
	      
	      (if (and (bufferp outputbuffer) (buffer-live-p outputbuffer))
		  (save-excursion
		    (set-buffer outputbuffer)
		    (goto-char (point-max))
		    (insert "----> PAW killed by user")
		    ) ; end save-excursion
		) ; end if we have an outputbuffer
	      
	      (if (and (bufferp logbuffer) (buffer-live-p logbuffer))
		  (save-excursion
		    (set-buffer logbuffer)
		    (goto-char (point-max))
		    (setq buffer-read-only nil)
		    (insert "----> PAW killed by user")
		    (setq buffer-read-only t)
		    ) ; end save-excursion
		) ; end if we have a logbuffer
	      
	      (save-excursion
		(set-buffer (plist-get node 'workbuffer))
		(setq paw-status "no process")
		) ; end save-excursion
	      
	      (if (and (bufferp outputbuffer)
		       (or (switch-to-buffer outputbuffer) t)
		       (y-or-n-p (format "Kill output buffer %s? " (buffer-name outputbuffer))))
		  (progn
		    (kill-buffer outputbuffer)
		    (setq count (1+ count))
		    ) ; end progn
		) ; end if
	      
	      (if (and (bufferp logbuffer)
		       (or (switch-to-buffer logbuffer) t)
		       (y-or-n-p (format "Kill log buffer %s? " (buffer-name logbuffer))))
		  (progn
		    (kill-buffer logbuffer)
		    (setq count (1+ count))
		    ) ; end progn
		) ; end if

	      (setq paw-process-list (delete node paw-process-list))
	      ) ; end let
	  (setq try-to-kill-old-outputs nil)
	  ) ; end if we really want to kill PAW after all
      ) ; end if there is a node at all

    (let ((name nil) (buffers nil))
      (if (string-match "^\\*PAW-out: \\(.+\\)\\*$" (buffer-name (current-buffer)))
	  (setq name (match-string 1 (buffer-name (current-buffer)))))
      (if (and (not name)
	       (string-match "^\\*PAW-log: \\(.+\\)\\*$" (buffer-name (current-buffer))))
	  (setq name (match-string 1 (buffer-name (current-buffer)))))
      (if (not name) (setq name (buffer-name (current-buffer))))

      (setq buffers (mapcar (function buffer-name) (buffer-list)))
      (while buffers
	(if (and try-to-kill-old-outputs
		 (string-match (concat "^\\*PAW-out: " name "\\*$") (car buffers))
		 (or (switch-to-buffer (get-buffer (car buffers))) t)
		 (y-or-n-p (format "Kill (suspected output) buffer %s? " (car buffers))))
	    (progn
	      (kill-buffer (get-buffer (car buffers)))
	      (setq count (1+ count))
	      ) ; end progn
	  ) ; end if
	(if (and (string-match (concat "^\\*PAW-log: " name "\\*") (car buffers))
		 (or (switch-to-buffer (get-buffer (car buffers))) t)
		 (y-or-n-p (format "Kill (suspected log) buffer %s? " (car buffers))))
	    (progn
	      (kill-buffer (get-buffer (car buffers)))
	      (setq count (1+ count))
	      ) ; end progn
	  ) ; end if
	(setq buffers (cdr buffers))
	) ; end while buffers

      ) ; end let

;    (set-window-configuration oldconf)
    (message (format "%s buffers deleted" count))
    ) ; end let
  )

(defun paw-execute-line (keep-output)
  "Send the current line to PAW for execution.  If you want to execute
loops or conditionals (do, while, if, etc...), use paw-execute-region
(C-c C-w).  If you want to be prompted for the command, rather than
type it in your buffer, use paw-execute (C-c C-c)."
  (interactive "P")

  (let ((node) (comment t) (start) (end) (input))
    (setq node (paw-find-node 'workbuffer (current-buffer)))
    (if (not node) (error "This is not a work buffer for an active PAW process"))
    (if (plist-get node 'query-prompt)
	(error "PAW is asking you a question; either answer it or C-g to cancel"))

    (while comment
      (save-excursion
	(beginning-of-line)
	(setq comment (or (looking-at "[ \t]*\\*")
			  (looking-at "[ \t]*$")))
	) ; end save-excursion
      (if comment (next-line 1))
      )

    (save-excursion
      (beginning-of-line)
      (setq start (point))
      (end-of-line)
      (setq end (point))
      ) ; end save-excursion
    (setq input (string-make-unibyte (buffer-substring start end)))
    (paw-execute (or (plist-get node 'commands) keep-output) input)
    (next-line 1)
    ) ; end let
  )

(defun paw-execute-region (keep-output)
  "Send the current region to PAW for execution (via a temporary
file).  This is provided for executing loops and conditionals (do,
while, if, etc...) which can't be entered directly on the command
line, only in a separate file.  Line-by-line execution is available
in a command prompt via paw-execute (C-c C-c) and in a buffer via
paw-execute line (C-j)."
  (interactive "P")

  (if (null (mark)) (error "No mark set in this buffer"))

  (let ((filename (concat paw-temporary-directory
			  "/pawtmp-"
			  (number-to-string (random 10000))
			  ".kumac")))
    (write-region (mark) (point) filename nil nil nil t)
    (paw-execute keep-output
		 (concat "exec " filename)
		 filename
		 (buffer-substring (mark) (point)))
    ) ; end let
  )

(defun paw-execute (keep-output &optional input filename fullinput)
  "Send a line to PAW for execution.  If you are using this command
interactively, you will be prompted for a line of PAW code.  To
execute a line from a buffer, use paw-execute-line (C-j)."
  (interactive "P")
  
  (let (node)
    (setq node (paw-find-node 'workbuffer (current-buffer)))
    (if (null node) (setq node (paw-find-node 'outputbuffer (current-buffer))))
    (if (null node) (setq node (paw-find-node 'logbuffer (current-buffer))))
    (if (or (null node)
	    (not (eq (process-status (plist-get node 'process)) 'run)))
	(error "There is no living PAW process associated with this buffer")

      (if (null input)
	  (setq input (read-from-minibuffer "PAW > " nil nil nil 'paw-history))
	) ; end if you need to read a command

      (if (and (not keep-output)
	       (bufferp (plist-get node 'outputbuffer))
	       (buffer-live-p (plist-get node 'outputbuffer)))
	  (save-excursion
	    (set-buffer (plist-get node 'outputbuffer))
	    (erase-buffer)
	    ) ; end save-excursion
	) ; end if not keep-output

      (paw-append-command node input filename)
      (process-send-string (plist-get node 'process) (format "%s\n" input))
      (save-excursion
	(set-buffer (plist-get node 'workbuffer))
	(setq paw-status "run")
	) ; end save-excursion

      (if (and filename fullinput)
	  (save-excursion
	    (set-buffer (plist-get node 'logbuffer))
	    (setq buffer-read-only nil)
	    (goto-char (point-max))
	    (insert (concat "*** Contents of " filename ":\n"))
	    (insert fullinput)
	    (insert "*** End of file.\nPAW > ")
	    (setq buffer-read-only t)
	    
	    (set-buffer (plist-get node 'outputbuffer))
	    (goto-char (point-max))
	    (insert (concat "*** Contents of " filename ":\n"))
	    (insert fullinput)
	    (insert "*** End of file.\nPAW > ")
	    ) ; end save-excursion
	) ; end if

      ) ; end if node and process are okay
    ) ; end let
  )

(defun paw-abort-command (&optional process)
  "Send a SIGINT to PAW, so that it will abort its current command.
This can be used when PAW is crunching away at some too-difficult
calculation or when it is annoyingly asking you for interactive
input."
  (interactive)

  (let (node)
    (if (null process)
	(progn
	  (setq node (paw-find-node 'workbuffer (current-buffer)))
	  (if (null node) (setq node (paw-find-node 'outputbuffer (current-buffer))))
	  (if (null node) (setq node (paw-find-node 'logbuffer (current-buffer))))
	  (if (or (null node)
		  (not (eq (process-status (plist-get node 'process)) 'run)))
	      (error "There is no living PAW process associated with this buffer")
	    (setq process (plist-get node 'process))
	    ) ; end if node and process is okay
	  ) ; end progn
      ) ; end if we need to get the process
    (if process (interrupt-process process))
    ) ; end let
  )

;;;  INTERNAL FUNCTIONS   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun paw-find-node (type value)
  "Return a node from `paw-process-list' that corresponds to a value
of the given type."

  (let ((i 0) (node nil))
    (while (< i (length paw-process-list))
      (if (eq (plist-get (nth i paw-process-list) type) value)
	  (setq node (nth i paw-process-list))
	) ; end if
      (setq i (1+ i))
      ) ; end while
    node
    ) ; end let
  )

(defun paw-append-command (node input filename)
  "Adds a command to a node's `commands' list."
  (let ((commands (plist-get node 'commands)))
    (setq commands (append commands (list (list 'input input 'filename filename))))
    (plist-put node 'commands commands)
    ) ; end let
  )

(defun paw-pop-command (node)
  "Removes a command from a node's `commands' list."
  (let ((commands (plist-get node 'commands)))
    (let ((filename (plist-get (car commands) 'filename)))
      (if filename
	  (progn
	    (delete-file filename)
	    (message (concat "Wrote, executed and deleted " filename))
	    ) ; end progn
	) ; end if
      ) ; end let

    (setq commands (cdr commands))
    (plist-put node 'commands commands)
    ) ; end let
  )

(defun paw-filter (process output)
  "Overwrites the associated output buffer with the PAW output, and
appends it to the log."

  (let ((node (paw-find-node 'process process))
	(start) (end) (commands-to-pop 0) (finished-last-command nil)
	(is-help-prompt) (is-interactive-prompt) (is-abort-prompt) (is-wait) (question)
	(beginning-window-configuration (current-window-configuration))
	(window-top (window-start)))

    (let ((outputbuffer (plist-get node 'outputbuffer))
	  (logbuffer (plist-get node 'logbuffer)))
      (if (and (bufferp outputbuffer) (buffer-live-p outputbuffer))
	  nil ; everything's fine
	(setq outputbuffer (get-buffer-create
			    (format "*PAW-out: %s*" (substring (process-name process) 5))))
	(save-excursion (set-buffer outputbuffer) (paw-log-mode) (setq truncate-lines t))
	(plist-put node 'outputbuffer outputbuffer)

	) ; end if
      (if (and (bufferp logbuffer) (buffer-live-p logbuffer))
	  nil ; everything's fine
	(setq logbuffer (generate-new-buffer
			 (format "*PAW-log: %s*" (substring (process-name process) 5))))
	(save-excursion (set-buffer logbuffer) (paw-log-mode) (setq buffer-read-only t))
	(plist-put node 'logbuffer logbuffer)
	) ; end if
      ) ; end let

;;     (let ((tmpbuffer (get-buffer-create
;; 		      (format "*PAW-tmp: %s*" (substring (process-name process) 5))))
;; 	  (found-end nil) (found-start) (found-chars nil))
;;       (save-excursion
;; 	(set-buffer tmpbuffer)
;; 	(erase-buffer)
;; 	(insert output)
;; 	(goto-char (point-min))
;;  	(while (re-search-forward "+\$" nil t)
;;  	  (setq found-end (point))
;;  	  (re-search-backward "+\$" nil t)
;;  	  (setq found-start (point))
;;  	  (setq found-chars (1- (- found-end found-start)))
;;  	  (delete-region found-start found-end)
;;  	  (setq found-end (point))
;;  	  (goto-char (max (- (point) found-chars) (point-min)))
;;  	  (setq found-start (point))
;;  	  (delete-region found-start found-end)
;;  	  ) ; end while we see 
;; 	(setq output (buffer-substring (point-min) (point-max)))
;; 	) ; end save-excursion
;;       (kill-buffer tmpbuffer)
;;       ) ; end let construction for cleaning up output

    (save-excursion
      (set-buffer (plist-get node 'outputbuffer))
      (goto-char (point-max))
      (insert output)
      ) ; end save-excursion

    (save-excursion
      (set-buffer (plist-get node 'logbuffer))
      (goto-char (point-max))
      (setq start (point))
      (setq buffer-read-only nil)
      (insert output)
      (setq buffer-read-only t)
      (setq end (point))

      (goto-char start)
      (while (search-forward-regexp "^PAW > " end t)
	(setq commands-to-pop (1+ commands-to-pop))
	) ; end while
      (goto-char end)

      (beginning-of-line)
      (setq finished-last-command (looking-at "PAW > $"))
      (setq is-help-prompt (looking-at "Enter a number.*: $"))
      (setq is-interactive-prompt (or (looking-at ".* (<CR>=.*)[ \t]*$")
				      (looking-at "Reenter initializer or Q to quit")))
      (setq is-abort-prompt (looking-at "You keep hitting"))
      (setq is-wait (looking-at "Type <CR> to continue or Q to quit"))

      (if (or is-help-prompt is-interactive-prompt is-abort-prompt is-wait)
	  (let (start end)
	    (setq start (point))
	    (end-of-line)
	    (setq end (point))
	    (setq question (buffer-substring start end))
	    ) ; end let
	) ; end if-else in a query

      ) ; end save-excursion

    (paw-insert-prompt-in-output (plist-get node 'outputbuffer))
      
    (if finished-last-command
	(save-excursion
	  (set-buffer (plist-get node 'workbuffer))
	  (plist-put node 'query-prompt nil)
	  (if (string-equal paw-status "init")
	      (message (format "Starting PAW with %s... done!" paw-command-line)))
	  (setq paw-status "idle")

	  (if (plist-get node 'window-configuration)
	      (progn
		(set-window-configuration (plist-get node 'window-configuration))
		(plist-put node 'window-configuration nil)
		) ; end progn
	    ) ; end if we have a window configuration to restore

	  ) ; end save-excursion
      ) ; end if

    (while (> commands-to-pop 0)
      (paw-pop-command node)
      (setq commands-to-pop (1- commands-to-pop))
      ) ; end while

    (if (or is-help-prompt is-interactive-prompt is-abort-prompt is-wait)
	(progn
	  (set-window-start (selected-window) window-top)
	  (if (and is-help-prompt paw-help-takes-over)
	      (progn
		(switch-to-buffer (plist-get node 'outputbuffer))
		(if (not (plist-get node 'window-configuration))
		    (progn
		      (plist-put node 'window-configuration beginning-window-configuration)
		      (delete-other-windows)
		      ) ; end progn
		  ) ; end if we haven't yet saved the window configuration
		) ; end progn
	    (set-buffer (plist-get node 'workbuffer))
	    (paw-split-output)
	    ) ; end if
	  (plist-put node 'query-prompt t)
	  (paw-query-question process question (plist-get node 'outputbuffer)
			      (or is-interactive-prompt is-abort-prompt is-wait))
	  ) ; end progn
      ) ; end if

    (set-window-start (selected-window) window-top)
    ) ; end let
  )

(defun paw-insert-prompt-in-output (outputbuffer)
  "A tacky little function for inserting `PAW >' at the beginning of
the output buffer, when applicable."

  (save-excursion
    (set-buffer outputbuffer)
    (goto-char (point-min))
    (if (and (not (looking-at "PAW > ")) (not (looking-at "[ \t]*\\*"))) (insert "PAW > "))
    ) ; end save-excursion
  )

(defun paw-query-question (process question outputbuffer keep-old-output)
  "Forces the user to stop and answer a question posed by PAW."
  (let (response)
    (condition-case nil
	(setq response (read-from-minibuffer question nil nil nil 'paw-query-history))
      (quit
       (progn
	 (plist-put (paw-find-node 'process process) 'commands nil)
	 (paw-abort-command process)
	 (keyboard-quit)
	 ) ; end progn
       ) ; end quit handler
      ) ; end condition-case

    (if (not keep-old-output)
	(save-excursion
	  (set-buffer outputbuffer)
	  (erase-buffer)
	  ) ; save-excursion
      ) ; end if

    (process-send-string process (format "%s\n" response))
    (setq paw-status "help")
    ) ; end let
  )

(defun paw-sentinel (process event)
  "Handles the shocking event of a PAW crash."
  (let ((node (paw-find-node 'process process)))
    (let ((outputbuffer (plist-get node 'outputbuffer))
	  (logbuffer (plist-get node 'logbuffer)))

      (if (and event (bufferp outputbuffer) (buffer-live-p outputbuffer))
	  (save-excursion
	    (set-buffer outputbuffer)
	    (goto-char (point-max))
	    (insert "----> PAW ")
	    (insert event)
	    ) ; end save-excursion
	) ; end if

      (if (and event (bufferp logbuffer) (buffer-live-p logbuffer))
	  (save-excursion
	    (set-buffer logbuffer)
	    (goto-char (point-max))
	    (setq buffer-read-only nil)
	    (insert "----> PAW ")
	    (insert event)
	    (setq buffer-read-only t)
	    ) ; end save-excursion
	) ; end if

      (if (plist-get node 'workbuffer)
	  (save-excursion
	    (set-buffer (plist-get node 'workbuffer))
	    (setq paw-status "no process")
	    ) ; end save-excursion
	) ; end if workbuffer exists

      (setq paw-process-list (delete node paw-process-list))
      ) ; end inner let
    ) ; end outer let
  )

(defun paw-indent-line ()
  "Indent the current line in a way which is okay for PAW."
  (interactive)

  (let (indent special cursor line-start words-start move-cursor)
    (save-excursion
      (beginning-of-line)
      (if (= (point) (point-min))
	  (setq indent 0)
	(forward-line -1)
	(while (and (or (looking-at "[ \t]*$")
			(looking-at "[ \t]*\\*")
			) ; end or
		    (not (= (point) (point-min)))
		    ) ; end and
	  (forward-line -1)
	  ) ; end while
	(skip-chars-forward " \t")
	(setq indent (current-column))
	(setq special (or (looking-at "case")
			  (looking-at "if")
			  (looking-at "do")
			  (looking-at "for")
			  (looking-at "repeat")
			  (looking-at "while")
			  (looking-at "else")
			  )) ; end setq
	) ; end if not at beginning
      ) ; end save-excursion

    (save-excursion
      (setq cursor (point))
      (beginning-of-line)
      (setq line-start (point))
      (skip-chars-forward " \t")
      (setq words-start (point))
      (if special (setq indent (+ indent 2)))
      (if (looking-at "[ \t]*end") (setq indent (- indent 2)))
      (if (looking-at "[ \t]*else") (setq indent (- indent 2)))
      (if (< indent 0) (setq indent 0))
      (setq move-cursor (>= words-start cursor))

      (delete-region line-start words-start)
      (indent-to indent)

      (setq words-start (point))
      ) ; end save-excursion
      
    (if move-cursor (goto-char words-start))
    ) ; end let
  )
