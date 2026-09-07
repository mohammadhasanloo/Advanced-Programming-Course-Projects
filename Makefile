PROJECTS := robots cinema carwash library mafia utunes-cli utunes-server

# Soccer Stars links against SDL2 and is left out of the default build so that
# `make` succeeds on a machine without it. `make soccer-stars` builds it.
ALL := $(PROJECTS) soccer-stars

all: $(PROJECTS)

everything: $(ALL)

$(ALL):
	$(MAKE) -C projects/$@

clean:
	$(foreach p,$(ALL),$(MAKE) -C projects/$(p) clean;)

.PHONY: all everything clean $(ALL)
