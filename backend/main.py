import requests
import argparse

def get_arguments():
    ap = argparse.ArgumentParser()
    ap.add_argument('-b', '--brightness', required=True,
                    help='Brightness of the light bulb (20, 50, 75, 100)')
    args = vars(ap.parse_args())
    return args

def main():
  args = get_arguments()

  if args['brightness'] & int(args['brightness']) in [20, 50, 75, 100]:
    r = requests.get(f'https://maker.ifttt.com/trigger/set{args.brightness}/json/with/key/dJ4Od62pIDkyxQsDFCmLzkZfiEbSpJxbq_m00iXHuc-')
    print(r.status_code)

  else:
    print('Invalid brightness value')

if __name__ == '__main__': 
    main()