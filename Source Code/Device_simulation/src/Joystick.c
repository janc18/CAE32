#include "device_desc_pedals.h"
#include <errno.h>
#include <fcntl.h>
#include <linux/uhid.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static int uhid_write(int fd, const struct uhid_event *ev) {
  ssize_t ret;

  ret = write(fd, ev, sizeof(*ev));
  if (ret < 0) {
    fprintf(stderr, "Cannot write to uhid: %m\n");
    return -errno;
  } else if (ret != sizeof(*ev)) {
    fprintf(stderr, "Wrong size written to uhid: %zd != %zu\n", ret, sizeof(ev));
    return -EFAULT;
  } else {
    return 0;
  }
}

static int create(int fd) {
  struct uhid_event ev;

  memset(&ev, 0, sizeof(ev));
  ev.type = UHID_CREATE2;
  strcpy((char *)ev.u.create2.name, "CAE32 Steering Wheel");
  memcpy(ev.u.create2.rd_data, Pedals_descriptor, sizeof(Pedals_descriptor));
  ev.u.create2.rd_size = sizeof(Pedals_descriptor);
  ev.u.create2.bus = BUS_USB;
  ev.u.create2.vendor = 0x15d9;
  ev.u.create2.product = 0x0a37;
  ev.u.create2.version = 10;
  ev.u.create2.country = 0;

  return uhid_write(fd, &ev);
}

static void destroy(int fd) {
  struct uhid_event ev;

  memset(&ev, 0, sizeof(ev));
  ev.type = UHID_DESTROY;

  uhid_write(fd, &ev);
}

/* This parses raw output reports sent by the kernel to the device. A normal
 * uhid program shouldn't do this but instead just forward the raw report.
 * However, for ducomentational purposes, we try to detect LED events here and
 *
 * print debug messages for it. */
static void handle_output(struct uhid_event *ev) {
  /* LED messages are adverised via OUTPUT reports; ignore the rest */
  if (ev->u.output.rtype != UHID_OUTPUT_REPORT)
    return;
  /* LED reports have length 2 bytes */
  if (ev->u.output.size != 2)
    return;
  /* first byte is report-id which is 0x02 for LEDs in our rdesc */
  if (ev->u.output.data[0] != 0x2)
    return;

  /* print flags payload */
  fprintf(stderr, "LED output report received with flags %x\n", ev->u.output.data[1]);
}

static int event(int fd) {
  struct uhid_event ev;
  ssize_t ret;

  memset(&ev, 0, sizeof(ev));
  ret = read(fd, &ev, sizeof(ev));
  if (ret == 0) {
    fprintf(stderr, "Read HUP on uhid-cdev\n");
    return -EFAULT;
  } else if (ret < 0) {
    fprintf(stderr, "Cannot read uhid-cdev: %m\n");
    return -errno;
  } else if (ret != sizeof(ev)) {
    fprintf(stderr, "Invalid size read from uhid-dev: %zd != %zu\n", ret, sizeof(ev));
    return -EFAULT;
  }

  switch (ev.type) {
  case UHID_START:
    fprintf(stderr, "UHID_START from uhid-dev\n");
    break;
  case UHID_STOP:
    fprintf(stderr, "UHID_STOP from uhid-dev\n");
    break;
  case UHID_OPEN:
    fprintf(stderr, "UHID_OPEN from uhid-dev\n");
    break;
  case UHID_CLOSE:
    fprintf(stderr, "UHID_CLOSE from uhid-dev\n");
    break;
  case UHID_OUTPUT:
    fprintf(stderr, "UHID_OUTPUT from uhid-dev\n");
    handle_output(&ev);
    break;
  case UHID_OUTPUT_EV:
    fprintf(stderr, "UHID_OUTPUT_EV from uhid-dev\n");
    break;
  default:
    fprintf(stderr, "Invalid event from uhid-dev: %u\n", ev.type);
  }

  return 0;
}

static bool btn1_down;
static bool btn2_down;
static bool btn3_down;
static char rel_hor;
static char rel_ver;
static char wheel;
static char clutch;

static int send_event(int fd) {
  struct uhid_event ev;

  memset(&ev, 0, sizeof(ev));
  ev.type = UHID_INPUT2;
  ev.u.input2.size = 11;

  ev.u.input2.data[0] = 0x1;
  if (btn1_down)
    ev.u.input2.data[1] |= 0x1;
  if (btn2_down)
    ev.u.input2.data[1] |= 0x2;
  if (btn3_down)
    ev.u.input2.data[1] |= 0x4;

  ev.u.input2.data[2] = rel_hor;
  ev.u.input2.data[3] = rel_ver;
  ev.u.input2.data[4] = wheel;
  ev.u.input2.data[5] = clutch;

  return uhid_write(fd, &ev);
}

static int keyboard(int fd) {
  char buf[128];
  ssize_t ret, i;

  ret = read(STDIN_FILENO, buf, sizeof(buf));
  if (ret == 0) {
    fprintf(stderr, "Read HUP on stdin\n");
    return -EFAULT;
  } else if (ret < 0) {
    fprintf(stderr, "Cannot read stdin: %m\n");
    return -errno;
  }

  for (i = 0; i < ret; ++i) {
    switch (buf[i]) {
    case '1':
      btn1_down = !btn1_down;
      ret = send_event(fd);
      if (ret)
        return ret;
      break;
    case '2':
      btn2_down = !btn2_down;
      ret = send_event(fd);
      if (ret)
        return ret;
      break;
    case '3':
      btn3_down = !btn3_down;
      ret = send_event(fd);
      if (ret)
        return ret;
      break;
    case 'a':
      rel_hor--;
      ret = send_event(fd);
      // abs_hor = 0;
      if (ret)
        return ret;
      break;
    case 'd':
      rel_hor++;
      ret = send_event(fd);
      // abs_hor = 0;
      if (ret)
        return ret;
      break;
    case 'w':
      rel_ver++;
      ret = send_event(fd);
      // abs_ver = 0;
      if (ret)
        return ret;
      break;
    case 's':
      rel_ver--;
      ret = send_event(fd);
      // abs_ver = 0;
      if (ret)
        return ret;
      break;
    case 'r':
      wheel++;
      ret = send_event(fd);
      // wheel = 0;
      if (ret)
        return ret;
      break;
    case 'f':
      wheel--;
      ret = send_event(fd);
      // wheel = 0;
      if (ret)
        return ret;
      break;
    case 't':
      clutch++;
      ret = send_event(fd);
      if (ret)
        return ret;
      break;
    case 'g':
      clutch--;
      ret = send_event(fd);
      if (ret)
        return ret;
      break;

    case 'q':
      return -ECANCELED;
    default:
      fprintf(stderr, "Invalid input: %c\n", buf[i]);
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  int fd;
  const char *path = "/dev/uhid";
  struct pollfd pfds[2];
  int ret;
  struct termios state;

  ret = tcgetattr(STDIN_FILENO, &state);
  if (ret) {
    fprintf(stderr, "Cannot get tty state\n");
  } else {
    state.c_lflag &= ~ICANON;
    state.c_cc[VMIN] = 1;
    ret = tcsetattr(STDIN_FILENO, TCSANOW, &state);
    if (ret)
      fprintf(stderr, "Cannot set tty state\n");
  }

  if (argc >= 2) {
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
      fprintf(stderr, "Usage: %s [%s]\n", argv[0], path);
      return EXIT_SUCCESS;
    } else {
      path = argv[1];
    }
  }

  fprintf(stderr, "Open uhid-cdev %s\n", path);
  fd = open(path, O_RDWR | O_CLOEXEC);
  if (fd < 0) {
    fprintf(stderr, "Cannot open uhid-cdev %s: %m\n", path);
    return EXIT_FAILURE;
  }
  fprintf(stderr, "Create uhid device\n");
  ret = create(fd);
  if (ret) {
    close(fd);
    return EXIT_FAILURE;
  }

  pfds[0].fd = STDIN_FILENO;
  pfds[0].events = POLLIN;
  pfds[1].fd = fd;
  pfds[1].events = POLLIN;

  fprintf(stderr, "Press 'q' to quit...\n");
  while (1) {
    ret = poll(pfds, 2, -1);
    if (ret < 0) {
      fprintf(stderr, "Cannot poll for fds: %m\n");
      break;
    }
    if (pfds[0].revents & POLLHUP) {
      fprintf(stderr, "Received HUP on stdin\n");
      break;
    }
    if (pfds[1].revents & POLLHUP) {
      fprintf(stderr, "Received HUP on uhid-cdev\n");
      break;
    }

    if (pfds[0].revents & POLLIN) {
      int counter = 0; //TODO: Remove termios functions
      while (1) {
        sleep(1);
        if (counter > 255) {
          counter = 0;
          rel_hor=0;
          rel_ver=0;
          wheel=0;
          clutch=0;
        }
        counter++;
        rel_hor++;
        rel_ver++;
        wheel++;
        clutch++;
        ret = send_event(fd);
        if (ret)
          break;
      }
    }
    if (pfds[1].revents & POLLIN) {
      ret = event(fd);
      if (ret)
        break;
    }
  }
  printf("ds\n");

  fprintf(stderr, "Destroy uhid device\n");
  destroy(fd);
  return EXIT_SUCCESS;
}
